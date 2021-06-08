<template>
  <q-page>
    <div class="row q-col-gutter-md justify-center">
      <div class="col-12 col-md-7 col-lg-6 q-gutter-y-md">
        <h5 class="q-pt-lg q-mb-xs">
          Build PSBT
        </h5>
        <q-card class="q-mt-lg">
          <q-card-section>
            <q-form @submit="findUtxos" class="q-gutter-md">
              <div class="row">
                <div class="col-12">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="xPub"
                    label="xpub/zpub"
                  ></q-input>
                </div>
              </div>
              <div class="row">
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
                <div class="col-3">
                  <q-btn-dropdown :label="network">
                    <q-list>
                      <q-item
                        clickable
                        v-close-popup
                        @click="() => selectNetwork('mainnet')"
                      >
                        <q-item-section>
                          <q-item-label>Mainnet</q-item-label>
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
                        @click="() => selectNetwork('simnet')"
                      >
                        <q-item-section>
                          <q-item-label>Simnet</q-item-label>
                        </q-item-section>
                      </q-item>
                    </q-list>
                  </q-btn-dropdown>
                </div>
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
              Transactions:
            </h6>
          </q-card-section>
          <q-card-section>
            <q-table
              :data="data"
              :columns="columns"
              row-key="name"
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

import axios from "axios";

export default {
  data() {
    return {
      xPub: "",
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
          name: "desc",
          required: true,
          label: "Transaction id",
          align: "left",
          field: row => row.name,
          format: val => `${val}`,
          sortable: true
        },
        {
          name: "amount",
          align: "center",
          label: "Amount",
          field: "amount",
          sortable: true
        },
        { name: "date", label: "Date", field: "date", sortable: true }
      ],
      data: [
        {
          name: "12c6DSiU4Rq3P4ZxziKxzrL5LmMBrzjrJX",
          amount: 159,
          date: "10.10.21"
        }
      ]
    };
  },
  methods: {
    selectNetwork(network) {
      this.network = network;
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

    async findUtxos() {
      console.log("############### findUtxos");
      // const x = await axios({
      //   method: "GET",
      //   url:
      //     "mempool/api/tx/0817faa843ea242d8cbd558a4fc977f2efbdc6d8aa7213a46fc419d488920a45"
      // });
      // console.log("x", x);
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
