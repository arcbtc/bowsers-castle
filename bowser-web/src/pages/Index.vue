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
  </q-page>
</template>

<script>
export default {
  name: "PageIndex",
  methods: {
    async connectDevice() {
      console.log("poo");
      let connected = false;
      let keepReading = true;
      let reader;
      var port;
      if (!connected) {
        port = await navigator.serial.requestPort();
        await port.open({ baudRate: 115200 });
      }
      if (port) {
        connected = true;
      } else {
        connected = false;
      }

      const textEncoder = new TextEncoderStream();
      const writableStreamClosed = textEncoder.readable.pipeTo(port.writable);

      const writer = textEncoder.writable.getWriter();
      var x = document.getElementById("myText").value;
      await writer.write(x);

      document
        .getElementById("cancelbow")
        .addEventListener("click", function () {
          port.close();
        });
    },
  },
};
</script>
