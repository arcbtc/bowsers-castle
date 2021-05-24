<template>
  <q-page>
    <div class="row q-col-gutter-md justify-center">
      <div class="col-12 col-md-7 col-lg-6 q-gutter-y-md">
        <h5 class="q-pt-lg q-mb-xs">
          Verify address: {{ btcVerifyAddress
          }}<q-tooltip
            >This `Verify address` MUST be the same as the one on the hardware
            wallet!</q-tooltip
          >
        </h5>
        <q-card class="q-mt-lg">
          <q-card-section>
            <q-form @submit="sendFunds" class="q-gutter-md">
              <div class="row">
                <div class="col-9">
                  <q-input
                    class="q-pr-md"
                    filled
                    dense
                    v-model="btcSendAddress"
                    label="Bitcoin address"
                  ></q-input>
                </div>
                <div class="col-3">
                  <q-input
                    filled
                    dense
                    v-model="btcSendAmount"
                    label="Amount"
                  ></q-input>
                </div>
              </div>

              <q-btn
                unelevated
                color="primary"
                :disable="btcSendAddress == '' || btcSendAmount < 0.0001"
                type="submit"
                >Send bitcoin</q-btn
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
      <div class="col-12 col-md-3 q-gutter-y-md">
        <q-card>
          <q-card-section>
            <h6 class="text-subtitle1 q-mt-none q-mb-sm">
              Receive address
              <q-btn
                flat
                @click="getFreshAddress"
                dense
                color="primary"
                label="get fresh address"
              />
            </h6>
          </q-card-section>
          <center>
            <vue-qrcode style="width:50%;" :value="btcCurrentAddress" />

            <q-card-section class="q-px-auto">
              <q-btn
                dense
                unelevated
                color="primary"
                @click="copyToClip(btcCurrentAddress)"
              >
                <div class="cursor-pointer">
                  <q-tooltip> Copy to clipboard </q-tooltip>
                  {{ btcCurrentAddress }}
                </div>
              </q-btn>
            </q-card-section>
          </center>
        </q-card>

        <q-card>
          <q-card-section>
            <h6 class="text-subtitle1 q-mt-none q-mb-sm">
              Bowser uses
              <a target="_blank" href="https://mempool.space">mempool.space</a>
              api for transaction data,<br />you can also use use your own
              mempool.space
            </h6>
          </q-card-section>
          <q-card-section class="q-px-auto">
            <q-btn unelevated color="primary" icon="edit">
              <div class="cursor-pointer">
                <q-tooltip> Point to another Mempool </q-tooltip>
                {{ this.mempool.endpoint }}
                <q-popup-edit v-model="mempool.endpoint">
                  <q-input color="accent" v-model="mempool.endpoint"> </q-input>
                  <center>
                    <q-btn flat dense @click="updateMempool()" v-close-popup
                      >set</q-btn
                    >
                    <q-btn flat dense v-close-popup>cancel</q-btn>
                  </center>
                </q-popup-edit>
              </div>
            </q-btn>
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
import VueQrcode from "vue-qrcode";

export default {
  components: {
    VueQrcode
  },
  data() {
    return {
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

    async sendFunds() {},
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
