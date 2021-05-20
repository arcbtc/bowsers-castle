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
          Are you sure you want to hard reset this device?
          <q-btn
            class="q-ml-lg q-pl-md q-pr-md"
            @click="hardReset()"
            outline
            dense
            style="color: goldenrod;"
            label="Ok"
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
                @click="confirmDelete = true"
                dense
                color="primary"
                label="hard reset"
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
export default {
  data() {
    return {
      pinPad: false,
      confirmDelete: false,
      waitUntil: false,
      pin: [],
      pinTemp: "",
      port: {},
      writableStreamClosed: {},
      reader: null,
      writer: null,
      readableStreamClosed: {},
      breakBool: false,
      readMessage: []
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
        this.pinPad = true;
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
      self.writer = await self.port.writable.getWriter();
      await self.writer.write(encoder.encode(data));
      await self.writer.releaseLock();
      self.writer = undefined;
      if (self.port) {
        try {
          await self.port.close();
        } catch (e) {}
      }
    },

    async hardReset() {
      self = this;
      self.confirmDelete = false;
      self.waitUntil = true;
      await self.writeData("HARD RESET");

      var refreshIntervalId = setInterval(async function() {
        await self.readPort();
        var hodler = self.readMessage;
        const hodlerString = await self.ab2str(hodler);
        console.log(hodlerString);

        var hodlerArr = hodlerString.split(",");
        console.log(hodlerArr);

        if (hodlerArr.includes("PINSTART") == true) {
          self.waitUntil = false;
          self.breakBool = true;
          clearInterval(refreshIntervalId);
        }
      }, 2000);
      self.breakBool = false;
    },
    async softResetReload() {
      this.writeData("SOFT RESET");
      location.reload();
    },
    async softReset() {
      this.writeData("SOFT RESET");
    },
    async callPin() {
      this.writeData("CONNECT");
    },
    async sendPin() {
      self = this;
      self.sendProcessing();
      await setTimeout(async function() {
        console.log(self.pin);
        console.log(self.pin.join().replaceAll(",", ""));
        self.writeData("PIN " + self.pin.join().replaceAll(",", ""));
      }, 2000);
      // await this.readIncoming();
      var refreshIntervalId = setInterval(async function() {
        await self.readPort();
        var hodler = self.readMessage;
        const hodlerString = await self.ab2str(hodler);
        var hodlerArr = hodlerString.split(",");
        console.log(hodlerArr);

        if (hodlerArr.includes("PINPASS") == true) {
          self.pinPad = false;
          self.leftDrawerOpen = true;
          clearInterval(refreshIntervalId);
        }
        if (hodlerArr.includes("PINFAIL") == true) {
          console.log("failed");
          self.pin = [];
          clearInterval(refreshIntervalId);
        }
      }, 2000);
    },
    async sendProcessing() {
      this.writeData("PROCESS");
    },
    async ab2str(buf) {
      return String.fromCharCode.apply(null, new Uint16Array(buf));
    }
  },
  created() {}
};
</script>
