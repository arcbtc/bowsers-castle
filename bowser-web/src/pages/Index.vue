<template>
  <q-page class="flex flex-center">
    <div class="column">
      <div class="col-11">
        <center>
          <q-btn
            size="35px"
            rounded
            color="primary"
            @click="connectDevice()"
            icon="link"
          >
            Connect Device</q-btn
          >
        </center>
      </div>
      <div class="col-1">
        <center>
          <q-card class="q-mt-md">
            Bowser Wallet is free and open-source, runs 100% in <br />
            your browser, can be used locally and can be used offline!<br />
            <a href="https://github.com/arcbtc/little-bowser"
              >https://github.com/arcbtc/little-bowser</a
            >
          </q-card>
        </center>
      </div>
    </div>

    <q-dialog v-model="confirmDelete">
      <q-card>
        <q-card-section class="row q-mx-auto q-pt-xl">
          Are you sure you want to delete EVERYTHING and hard reset this device?
        </q-card-section>
        <q-card-actions align="right">
          <q-btn
            class="q-ml-lg q-pl-md q-pr-md"
            @click="hardReset()"
            outline
            dense
            style="color: red;"
            label="I understand"
          />
        </q-card-actions>
      </q-card>
    </q-dialog>

    <q-dialog v-model="errorPopup">
      <q-card>
        <q-card-section class="row q-mx-auto q-pt-xl">
          <h3>FAILED TO CONNECT, TRY AGAIN</h3>
          <q-icon
            name="warning"
            class="text-primary"
            style="font-size: 15rem;"
          />
        </q-card-section>
      </q-card>
    </q-dialog>

    <q-dialog persistent v-model="waitUntil">
      <q-card>
        <q-card-section class="row q-mx-auto q-pt-xl">
          <div class="row">
            <div class="col-10">
              Copy your backup words somewhere secure and private,
              <br />then enter an 8 digit pin, using refernce bowser pinpad.
            </div>
            <div class="col-2">
              <img
                src="https://i.imgur.com/rnPG6wd.gif"
                style="width:70px"
                class="q-mx-auto "
              />
            </div>
          </div>
        </q-card-section>

        <q-card-actions align="right">
          <q-btn
            @click="softResetReload()"
            outline
            dense
            style="color: goldenrod;"
            label="Cancel"
          ></q-btn>
        </q-card-actions>
      </q-card>
    </q-dialog>

    <q-dialog v-model="pinPad" persistent>
      <q-card>
        <center>
          <p
            dense
            class="q-pt-xl"
            style="font-size: 50px; line-height: 60%;"
            value="pin.length()"
            v-if="pinAmount.length < 1"
          >
            Enter pin
            <br /><small style="font-size: 10px;padding-left: 150px;"
              >or
              <q-btn
                flat
                :disabled="firstPin == 1"
                @click="confirmDelete = true"
                dense
                color="primary"
                label="hard reset"/>/<q-btn
                flat
                :disabled="firstPin == 1"
                @click="confirmDelete = true"
                dense
                color="primary"
                label="restore"
            /></small>
          </p>
          <p
            dense
            class="q-pt-xl"
            style="font-size: 50px;"
            value="pin.length()"
            v-else
          >
            {{ pinAmount }}
          </p>
        </center>
        <q-card-section class="row q-mx-auto q-pt-none" style="width:70%;">
          <div class="row" style="width:100%;">
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                outline
                color="primary"
                @click="pin.push(1)"
                style="width:100%;"
                padding="lg"
                size="xl"
                >*</q-btn
              >
            </div>
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(2)"
                style="width:100%;"
                padding="lg"
                size="xl"
                outline
                color="primary"
                >*</q-btn
              >
            </div>
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(3)"
                size="xl"
                outline
                color="primary"
                style="width:100%;"
                padding="lg"
                >*</q-btn
              >
            </div>
          </div>

          <div class="row" style="width:100%;">
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(4)"
                style="width:100%;"
                padding="lg"
                size="xl"
                outline
                color="primary"
                >*</q-btn
              >
            </div>
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(5)"
                style="width:100%;"
                padding="lg"
                size="xl"
                outline
                color="primary"
                >*</q-btn
              >
            </div>
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(6)"
                size="xl"
                outline
                color="primary"
                style="width:100%;"
                padding="lg"
                >*</q-btn
              >
            </div>
          </div>

          <div class="row" style="width:100%;">
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(7)"
                style="width:100%;"
                padding="lg"
                size="xl"
                outline
                color="primary"
                >*</q-btn
              >
            </div>
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(8)"
                style="width:100%;"
                padding="lg"
                size="xl"
                outline
                color="primary"
                >*</q-btn
              >
            </div>
            <div class="col">
              <q-btn
                :disabled="yesHW == 0"
                unelevated
                @click="pin.push(9)"
                size="xl"
                outline
                color="primary"
                style="width:100%;"
                padding="lg"
                >*</q-btn
              >
            </div>
          </div>
        </q-card-section>

        <q-card-actions align="right">
          <q-btn flat label="Cancel" color="primary" v-close-popup />
          <q-btn
            v-if="pin.length == 8"
            flat
            label="Connect"
            color="primary"
            @click="sendPin()"
          />
          <q-btn
            v-else
            flat
            disabled
            label="Connect"
            color="primary"
            v-close-popup
          />
        </q-card-actions>
      </q-card>
    </q-dialog>
  </q-page>
</template>

<script>
const bjs = require("bitcoinjs-lib");
var b58 = require("bs58check");
import { QSpinnerGears } from "quasar";
export default {
  data() {
    return {
      pinPad: false,
      confirmDelete: false,
      waitUntil: false,
      errorPopup: false,
      pin: [],
      pinTemp: "",
      port: {},
      writableStreamClosed: {},
      reader: null,
      writer: null,
      readableStreamClosed: {},
      breakBool: false,
      readMessage: [],
      yesHW: 0,
      firstPin: 0
    };
  },
  name: "PageIndex",

  computed: {
    pinAmount: function() {
      self = this;
      self.pinTemp = "";
      for (var i = 0; i < self.pin.length; i++) {
        self.pinTemp = self.pinTemp + "*";
      }
      return self.pinTemp;
    }
  },
  methods: {
    async connectDevice() {
      self = this;
      let connected = false;
      if (!connected) {
        self.port = await navigator.serial.requestPort();
      }
      if (self.port) {
        self.pin = [];
        connected = true;
        await this.callPin();
      } else {
        connected = false;
      }
    },

    ////////////////////COMMANDS////////////////////////

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

    async hardReset() {
      self = this;
      self.firstPin = 1;
      self.confirmDelete = false;
      self.waitUntil = true;
      self.$q.notify({
        spinner: QSpinnerGears,
        message: "Wiping EVERYTHING...",
        timeout: 6000
      });
      await self.writeData("HARDRESET");

      var refreshIntervalId = setInterval(async function() {
        await self.readPort();
        var hodler = self.readMessage;
        const hodlerString = await self.ab2str(hodler);
        console.log(hodlerString);

        var hodlerArr = hodlerString.split(",");
        console.log(hodlerArr);

        if (hodlerArr.includes("PINSTART") == true) {
          self.yesHW = 1;
          self.waitUntil = false;
          self.breakBool = true;
          self.$q.notify({
            message: "Enter an 8 digit pin",
            caption: "Use the Bowser for a pin reference!",
            color: "primary"
          });
          clearInterval(refreshIntervalId);
        }
      }, 2000);
      self.breakBool = false;
    },
    async softResetReload() {
      this.writeData("SOFTRESET");
      location.reload();
    },
    async softReset() {
      this.writeData("SOFTRESET");
    },
    async callPin() {
      self = this;
      self.writeData("CONNECT");
      var counter = 0;
      self.$q.notify({
        spinner: QSpinnerGears,
        message: "connecting...",
        timeout: 2000
      });
      var refreshIntervalId = setInterval(async function() {
        await self.readPort();
        var hodler = self.readMessage;
        const hodlerString = await self.ab2str(hodler);
        var hodlerArr = await hodlerString.split(",");
        console.log(hodlerArr);
        if (hodlerArr.includes("NOHWW") == true) {
          self.yesHW = 0;
          self.pinPad = true;
          self.$q.notify({
            message: "No wallet found on device",
            caption: "HARD RESET, or RESTORE"
          });
          clearInterval(refreshIntervalId);
        }
        if (hodlerArr.includes("YESHWW") == true) {
          self.yesHW = 1;
          self.pinPad = true;
          await self.writeData("HANDSHAKE");
          self.$q.notify({
            message: "Wallet found!",
            caption: "Please enter pin",
            color: "primary"
          });
          clearInterval(refreshIntervalId);
        }
        if (counter > 3) {
          self.$q.notify({
            message: "ERROR: Could not connect",
            caption: "Is the Bowser powered on?",
            color: "negative"
          });
          clearInterval(refreshIntervalId);
        }
        counter = counter + 1;
      }, 2000);
    },
    async sendPin() {
      self = this;
      sessionStorage.setItem("%P1", "");
      sessionStorage.setItem("%P2", "");
      sessionStorage.setItem("%P3", "");
      sessionStorage.setItem("zpub", "");
      sessionStorage.setItem("ADR", "");
      sessionStorage.setItem("VADDR", "");
      await self.sendProcessing();
      setTimeout(async function() {
        console.log(self.pin);
        console.log(self.pin.join().replaceAll(",", ""));
        await self.writeData("PIN" + self.pin.join().replaceAll(",", ""));
      }, 2000);
      // await this.readIncoming();
      var refreshIntervalId = setInterval(async function() {
        await self.readPort();
        var hodler = self.readMessage;
        const hodlerString = await self.ab2str(hodler);
        var hodlerArr = hodlerString.split(",");
        console.log(hodlerArr);

        for (var i = 0; i < hodlerArr.length; i++) {
          if (
            hodlerArr[i].substring(0, 3) == "%P1" &&
            sessionStorage.getItem("%P1").length < hodlerArr[i].length - 3
          ) {
            console.log(hodlerArr[i].length - 3);
            console.log(sessionStorage.getItem("%P1").length);
            console.log(sessionStorage.getItem("%P1"));
            sessionStorage.setItem(
              "%P1",
              hodlerArr[i].substring(3, hodlerArr[i].length)
            );
          } else if (
            hodlerArr[i].substring(0, 3) == "%P2" &&
            sessionStorage.getItem("%P2").length < hodlerArr[i].length - 3
          ) {
            sessionStorage.setItem(
              "%P2",
              hodlerArr[i].substring(3, hodlerArr[i].length)
            );
          } else if (
            hodlerArr[i].substring(0, 3) == "%P3" &&
            sessionStorage.getItem("%P3").length < hodlerArr[i].length - 3
          ) {
            sessionStorage.setItem(
              "%P3",
              hodlerArr[i].substring(3, hodlerArr[i].length)
            );
          } else if (
            hodlerArr[i].substring(0, 3) == "ADR" &&
            sessionStorage.getItem("ADR").length < hodlerArr[i].length - 3
          ) {
            sessionStorage.setItem(
              "ADR",
              hodlerArr[i].substring(3, hodlerArr[i].length)
            );
          }
        }
        if (hodlerArr.includes("PINPASS") == true) {
          var p1str = sessionStorage.getItem("%P1");
          var p2str = sessionStorage.getItem("%P2");
          var p3str = sessionStorage.getItem("%P3");
          sessionStorage.setItem("zpub", p1str + p2str + p3str);
          var vaddr = await self.getAddress(0);
          console.log("the addressString is" + vaddr);
          sessionStorage.setItem("VADDR", vaddr);

          self.pinPad = false;

          self.$router.push("wallet");
          clearInterval(refreshIntervalId);
        }
        if (hodlerArr.includes("PINFAILL") == true) {
          self.$q.notify({
            message: "ERROR: Pin failed",
            caption: "Use the Bowser wallet as a reference",
            color: "negative"
          });
          self.pin = [];
          clearInterval(refreshIntervalId);
        }
      }, 2000);
    },
    async sendProcessing() {
      await this.writeData("PROCESS");
    },
    async ab2str(buf) {
      return String.fromCharCode.apply(null, new Uint16Array(buf));
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
            .derive(1).publicKey
        })
      console.log(address);
      return address;
    }
  },
  created() {}
};
</script>
