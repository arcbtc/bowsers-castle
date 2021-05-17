<template>
  <q-layout view="lHh Lpr lFf">
    <q-header elevated>
      <q-toolbar>


        <q-toolbar-title> Bowser Wallet </q-toolbar-title>

        <div>Version v0.01</div>
      </q-toolbar>
    </q-header>

    <q-drawer
    v-show="leftDrawerOpen"
      v-model="leftDrawerOpen"

      bordered
      style="background-color: #1d1d1d"
    >
      <q-list>
        <q-item-label header class="text-grey-8">
          Essential Links
        </q-item-label>
        <EssentialLink
          v-for="link in essentialLinks"
          :key="link.title"
          v-bind="link"
        />
      </q-list>
      <img
        style="width: 50%"
        class="fixed-bottom-left"
        src="https://i.imgur.com/CfwfjBK.png"
      />
    </q-drawer>
    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>

</template>

<script>
import EssentialLink from "components/EssentialLink.vue";

const linksData = [
  {
    title: "Docs",
    caption: "quasar.dev",
    icon: "school",
    link: "https://quasar.dev",
  },
  {
    title: "Github",
    caption: "github.com/quasarframework",
    icon: "code",
    link: "https://github.com/quasarframework",
  },
  {
    title: "Discord Chat Channel",
    caption: "chat.quasar.dev",
    icon: "chat",
    link: "https://chat.quasar.dev",
  },
  {
    title: "Forum",
    caption: "forum.quasar.dev",
    icon: "record_voice_over",
    link: "https://forum.quasar.dev",
  },
  {
    title: "Twitter",
    caption: "@quasarframework",
    icon: "rss_feed",
    link: "https://twitter.quasar.dev",
  },
  {
    title: "Facebook",
    caption: "@QuasarFramework",
    icon: "public",
    link: "https://facebook.quasar.dev",
  },
  {
    title: "Quasar Awesome",
    caption: "Community Quasar projects",
    icon: "favorite",
    link: "https://awesome.quasar.dev",
  },
];


export default {
  data() {
    return {
      leftDrawerOpen: false,
      essentialLinks: linksData
    };
  },
  created() {
    this.$q.dark.set(true);
  },
  name: "MainLayout",
  components: { EssentialLink },
  methods: {
  launchPinPad(){
    this.pinPad = true;
  },
  loggedIn(){
    
    this.leftDrawerOpen = false;
    }
  },

};
</script>
