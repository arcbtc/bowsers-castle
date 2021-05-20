<template>
  <q-layout view="lHh Lpr lFf">
    <q-header elevated>
      <q-toolbar>
        <img src="~assets/bowser_logo.png" />
        <q-toolbar-title> </q-toolbar-title>

        <div>
          Version v0.01
        </div>
      </q-toolbar>
    </q-header>


    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>
</template>

<script>

export default {
  data() {
    return {
      leftDrawerOpen: false,
      showDraw: "fgndsf"
    };
  },
  computed: {
    currentRouteName() {
      if (this.$router.history.current.path.length == 1) {
        return true;
      } else {
        return false;
      }
    }
  },
  created() {
    this.$q.dark.set(true);

  },
  name: "MainLayout",

  methods: {
    launchPinPad() {
      this.pinPad = true;
    },
    loggedIn() {}
  }
};
</script>
