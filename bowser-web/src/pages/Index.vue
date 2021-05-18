<template>
  <q-page class="flex flex-center">
    <q-btn
      size="35px"
      rounded
      color="primary"
      @click="connectDevice()"
      icon="link"
    >
      Connect Device</q-btn
    >

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
              Please follow the instructions on your device...
              <br />Backup your word list somewhere safe!
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
      writer: {},
      writableStreamClosed: {},
      reader: null,
      readableStreamClosed: {},
      breakBool: false
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
    launchPinPad() {
      this.pinPad = true;
    },
    async connectDevice() {
      self = this;
      let connected = false;
      if (!connected) {
        self.port = await navigator.serial.requestPort();
      }
      if (self.port) {
        self.pin = [];
        connected = true;
        await this.launchPinPad();
        await this.callPin();
      } else {
        connected = false;
      }
    },

    ////////////////////COMMANDS////////////////////////

    //READING SERIAL//

    async readPort() {
      self = this;
      await self.port.open({ baudRate: 115200 });
      while (self.port && self.port.readable) {
        try {
          self.reader = await self.port.readable.getReader();
          for (;;) {
            const { value, done } = await self.reader.read();
            var message = await self.ab2str(value);
            var split = await message.split(",");
            console.log(split);
            if (split.includes("OVER")) {
              self.breakBool = true;
              break;
            }
            if (split.includes("PINSTART")) {
              self.waitUntil = false;
            }
            if (message == "PINPASS") {
              self.waitUntil = false;
            }
            if (message == "PINFAIL") {
              await self.softResetReload();
            }
          }
          self.reader.releaseLock();
          self.reader = undefined;
        } catch (e) {}
      }
      if (self.port) {
        try {
          await self.port.close();
        } catch (e) {}
      }
    },

    //WRITING TO SERIAL//

    async writeData(data) {
      self = this;
      const encoder = await new TextEncoder();
      await self.port.open({ baudRate: 115200 });
      const writer = await self.port.writable.getWriter();
      await writer.write(encoder.encode(data));
      await writer.releaseLock();
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
        if (self.breakBool == true) {
          clearInterval(refreshIntervalId);
        }
        }, 4000);
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
    },
    async sendProcessing() {
      this.writeData("PROCESS");
    },
    async ab2str(buf) {
  return String.fromCharCode.apply(null, new Uint16Array(buf));
}
  }
};
</script>
