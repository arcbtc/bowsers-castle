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
      pin: [],
      pinTemp: "",
      port: {},
      writer: {}
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
      let loggedIn = false;
      let keepReading = true;
      let reader;
      if (!connected) {
        self.port = await navigator.serial.requestPort();
        await self.port.open({ baudRate: 115200 });
      }
      if (self.port) {
        self.pin = [];
        connected = true;
        await this.connectWriter();
        this.launchPinPad();
        this.callPin();
      } else {
        connected = false;
      }
    },

    ////////////////////COMMANDS////////////////////////
    connectWriter() {
      self = this;
      console.log(self.port);
      const textEncoder = new TextEncoderStream();
      const writableStreamClosed = textEncoder.readable.pipeTo(
        self.port.writable
      );
      self.writer = textEncoder.writable.getWriter();
    },
    async hardReset() {
      await this.writer.write("HARD RESET");
    },
    async callPin() {
      await this.writer.write("CONNECT");
    },
    async sendPin() {
      self = this;
      self.sendProcessing();
      await setTimeout(async function(){   
        console.log(self.pin); 
        console.log(self.pin.join().replaceAll(",", ""));
        self.writer.write("PIN " + self.pin.join().replaceAll(",", ""));     
       }, 2000);
        
    },
    async sendProcessing() {
      await this.writer.write("PROCESS");
    }
  }
};
</script>
