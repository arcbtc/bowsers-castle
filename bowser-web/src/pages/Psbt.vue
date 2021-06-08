<template>
  <q-page>
    <div class="row q-col-gutter-md justify-center">
      <div class="col-12 col-md-10 col-lg-10 q-gutter-y-md">
        <h5 class="q-pt-lg q-mb-xs">
          Build PSBT
        </h5>
        <q-card class="q-mt-lg">
          <q-card-section>
            <q-form @submit="findUtxos" class="q-gutter-md">
              <div class="row">
                <div class="col-9">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="xPub"
                    label="xpub/zpub"
                  ></q-input>
                </div>
                <div class="col-3">
                  <q-btn-dropdown :label="network">
                    <q-list>
                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('bitcoin')"
                      >
                        <q-item-section>
                          <q-item-label>Bitcoin</q-item-label>
                        </q-item-section>
                      </q-item>

                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('testnet')"
                      >
                        <q-item-section>
                          <q-item-label>Testnet</q-item-label>
                        </q-item-section>
                      </q-item>

                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('regtest')"
                      >
                        <q-item-section>
                          <q-item-label>Regtest</q-item-label>
                        </q-item-section>
                      </q-item>
                    </q-list>
                  </q-btn-dropdown>
                </div>
              </div>
              <div class="row">
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="derivationRoot"
                    label="derivation root"
                  ></q-input>
                </div>
                <div class="col-1"></div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="derivationStartIndex"
                    label="derivation start index"
                  ></q-input>
                </div>
                <div class="col-1"></div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="derivationSize"
                    label="size"
                  ></q-input>
                </div>
                <div class="col-2"></div>
              </div>

              <q-btn
                unelevated
                color="primary"
                :disable="xPub == ''"
                type="submit"
                >Find UTXOs</q-btn
              >
            </q-form>
          </q-card-section>
        </q-card>

        <q-card class="q-mt-lg">
          <q-card-section>
            <h6 class="text-subtitle1 q-mt-none q-mb-sm">
              UTXOs:
            </h6>
          </q-card-section>
          <q-card-section>
            <q-table
              :data="data"
              :columns="columns"
              row-key="id"
              :pagination="pagination"
              dark
              color="amber"
            />
          </q-card-section>
        </q-card>
      </div>
    </div>
  </q-page>
</template>

<script>
const bjs = require("bitcoinjs-lib");
var b58 = require("bs58check");
import { QSpinnerGears } from "quasar";
import { copyToClipboard } from "quasar";

const utxoSvc = require("../services/utxo.service")("mempool");
// const feeSvc = require("./services/fee.service")("mempool");
const txSvc = require("../services/tx.service")("mempool");

export default {
  data() {
    return {
      xPub: "",
      derivationRoot: "0",
      derivationStartIndex: 0,
      derivationSize: 10,
      network: "testnet",

      mempool: {
        endpoint: "https://mempool.space"
      },
      btcVerifyAddress: sessionStorage.getItem("VADDR"),
      btcAddressNo: parseInt(sessionStorage.getItem("ADR")),
      btcCurrentAddress: "",
      btcSendAmount: 0,
      btcSendAddress: "",

      columns: [
        {
          name: "address",
          required: true,
          label: "Address",
          align: "left",
          field: row => row.address,
          format: val => `${val || ""}`,
          sortable: true
        },

        {
          name: "amount",
          align: "center",
          label: "Amount",
          field: "value",
          sortable: true
        },
        {
          name: "vout",
          align: "center",
          label: "VOut",
          field: "vout",
          sortable: true
        },
        {
          name: "txid",
          required: false,
          label: "Transaction ID",
          align: "left",
          field: row => row.txid,
          format: val => `${val || ""}`,
          sortable: true
        }
      ],
      pagination: {
        rowsPerPage: 30
      },
      data: []
    };
  },
  methods: {
    selectNetwork(network) {
      this.network = network;
    },
    async findUtxos() {
      console.log("############### findUtxos");
      try {
        const xPub = this.xPub.toLowerCase().startsWith("zpub")
          ? this.zpubToXpub(this.xPub)
          : this.xPub;
        const network = bjs.networks[this.network];
        const hdNode = bjs.bip32.fromBase58(xPub, network);

        const addressList = this.deriveAddresses(hdNode, {
          rootPath: this.derivationRoot,
          start: this.derivationStartIndex,
          size: this.derivationSize,
          network
        });
        this.data = addressList.map((address, index) => ({
          id: index,
          address
        }));
        const utxoPromisses = addressList.map(address => {
          return utxoSvc.getUtxosForAddress(address);
        });
        const allUtxos = await Promise.all(utxoPromisses);
        console.log("allUtxos", allUtxos);
        const data = [];
        allUtxos.forEach((utxos, index) => {
          if (!utxos.length) {
            data.push({
              id: data.length,
              address: addressList[index]
            });
            return;
          }
          utxos.forEach((utxo, i) => {
            data.push({
              id: data.length,
              address: i === 0 ? addressList[index] : "",
              txid: utxo.txid,
              value: utxo.value,
              vout: utxo.vout
            });
          });
        });
        this.data = data;
      } catch (err) {
        self.$q.notify({
          icon: "error",
          message: err.message || err
        });
      }

      // const tx = await txSvc.getTx(
      //   "0817faa843ea242d8cbd558a4fc977f2efbdc6d8aa7213a46fc419d488920a45"
      // );
      // console.log("tx", tx);
    },
    deriveAddresses(node, op = {}) {
      const start = op.start || 0;
      const size = op.size || 10;
      const rootPath = op.rootPath || "m/84'/0'/0'/0";
      const network = op.network || bjs.networks.testnet;

      const addresses = [];
      for (let i = start; i < start + size; i++) {
        const derivationPath = `${rootPath}/${i}`;
        const publicKey = node.derivePath(derivationPath).publicKey;
        const payment = bjs.payments.p2wpkh({
          pubkey: publicKey,
          network
        });
        addresses.push(payment.address);
      }
      return addresses;
    },
    zpubToXpub(zpub) {
      var data = b58.decode(zpub);
      data = data.slice(4);
      data = Buffer.concat([Buffer.from("0488b21e", "hex"), data]);
      return b58.encode(data);
    },
    //READING SERIAL//

    async readPort() {
      self = this;
      try {
        await self.port.open({ baudRate: 115200 });
      } catch (e) {
        try {
          await self.reader.releaseLock();
          self.reader = undefined;
          await self.port.close();
          await self.port.open({ baudRate: 115200 });
        } catch (e) {}
      }
      try {
        self.reader = self.port.readable.getReader();
        const { value, done } = await self.reader.read();
        if (value) {
          self.readMessage = value;
        }
        await self.reader.releaseLock();
        self.reader = undefined;
      } catch (e) {}
      if (self.port) {
        try {
          await self.port.close();
        } catch (e) {}
      }
    },
    //WRITING TO SERIAL//

    async writeData(data) {
      self = this;
      const encoder = new TextEncoder();
      try {
        await self.port.open({ baudRate: 115200 });
      } catch (e) {
        try {
          await self.writer.releaseLock();
          self.writer = undefined;
          await self.port.close();
          await self.port.open({ baudRate: 115200 });
        } catch (e) {}
      }
      try {
        self.writer = await self.port.writable.getWriter();
        await self.writer.write(encoder.encode(data));
        await self.writer.releaseLock();
        self.writer = undefined;
      } catch (e) {}
      if (self.port) {
        try {
          await self.port.close();
        } catch (e) {}
      }
    },
    async getFreshAddress() {
      self = this;
      self.$q.notify({
        spinner: QSpinnerGears,
        message: "Fetching address...",
        timeout: 6000
      });
      await self.writeData("ADR");

      var refreshIntervalId = setInterval(async function() {
        await self.readPort();
        var hodler = self.readMessage;
        const hodlerString = await self.ab2str(hodler);
        console.log(hodlerString);

        var hodlerArr = hodlerString.split(",");
        console.log(hodlerArr);
        for (var i = 0; i < hodlerArr.length; i++) {
          if (hodlerArr[i].substring(0, 3) == "ADR") {
            sessionStorage.setItem(
              "ADR",
              hodlerArr[i].substring(3, hodlerArr[i].length)
            );
            self.btcAddressNo = parseInt(sessionStorage.getItem("ADR"));
            clearInterval(refreshIntervalId);
          }
        }
      }, 2000);
    },

    async updateMempool() {
      self = this;
      self.mempool.endpoint = self.mempool;
    },
    async getTransactions() {
      self = this;
      self.mempool.endpoint = self.mempool;
    },
    getAddress(addNo) {
      function zpubToXpub(zpub) {
        var data = b58.decode(zpub);
        data = data.slice(4);
        data = Buffer.concat([Buffer.from("0488b21e", "hex"), data]);

        return b58.encode(data);
      }
      var xpub = zpubToXpub(sessionStorage.getItem("zpub"));
      var hdNode = bjs.bip32.fromBase58(xpub);
      console.log(hdNode.derive(0).derive(addNo).publicKey);

      const { address } = bjs.payments.p2wpkh({
        pubkey: bjs.bip32
          .fromBase58(xpub)
          .derive(0)
          .derive(addNo).publicKey
      });
      self.btcCurrentAddress = address;
    },
    copyToClip(data) {
      self = this;
      copyToClipboard(data)
        .then(() => {
          self.$q.notify({
            icon: "content_copy",
            message: "Copied"
          });
        })
        .catch(() => {
          self.$q.notify({
            icon: "error",
            message: "Copy failed"
          });
        });
    },
    async ab2str(buf) {
      return String.fromCharCode.apply(null, new Uint16Array(buf));
    }
  },
  created() {
    self = this;
    if (!sessionStorage.getItem("ADR")) {
      self.btcAddressNo = 1;
    }
    self.getAddress(self.btcAddressNo);
  }
};
</script>
