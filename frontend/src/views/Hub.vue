<template>
  <v-app class="app-hub">
    <v-app-bar app flat>
      <v-toolbar-title class="header-title">Berking</v-toolbar-title>
    </v-app-bar>
    <v-content>
      <v-container fluid class="full-height hub-btns">
        <v-row class="full-height hub-btns__row">
          <v-col cols="12" class="full-height text-center hub-btns__col1">
            <v-btn block color="primary" class="btn-banking mb-12" to="/berking"
              >Banking
            </v-btn>
            <v-btn
              outlined
              block
              color="primary"
              class="btn-terminal"
              to="/terminal"
              >Terminal
            </v-btn>
          </v-col>
        </v-row>
      </v-container>
    </v-content>
  </v-app>
</template>

<script>
export default {
  data() {
    return {
      center: 'center',
    };
  },
};
</script>

<style lang="scss">
@import '../assets/scss/variables.scss';
@import '../assets/scss/common.scss';

.app-hub {
  .v-toolbar {
    &__content {
      justify-content: center;

      border-bottom: 1px solid $accentColor;
    }

    &__title {
      font-family: $mainFont;
      font-size: 2.3rem !important;
      color: $accentColor;
    }
  }

  .hub-btns {
    padding-left: 30%;
    padding-right: 30%;

    .btn-banking,
    .btn-terminal {
      height: 15% !important;
      font-size: 1.5rem;
    }

    .btn-banking {
      margin-top: 20%;
    }
  }
}
</style>
