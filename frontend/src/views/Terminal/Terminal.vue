<template>
  <v-app class="app-terminal">
    <v-app-bar app flat>
      <v-toolbar-title>
        <router-link to="/terminal" tag="span" class="header-title">
          Berking
        </router-link>
        <v-chip color="primary" small>
          beta
        </v-chip>
      </v-toolbar-title>
    </v-app-bar>
    <v-content>
      <router-view></router-view>
    </v-content>
  </v-app>
</template>

<style lang="scss">
@import '../../assets/scss/variables.scss';
@import '../../assets/scss/common.scss';

.app-terminal {
  .v-toolbar {
    &__content {
      justify-content: center;

      border-bottom: 1px solid $accentColor;
    }

    .header-title {
      font-family: 'Great Vibes', cursive;
      font-size: 2.3rem !important;
      color: $accentColor;
      cursor: pointer;
    }
  }
}
</style>
