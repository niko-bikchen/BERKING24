<template>
  <v-container fluid class="full-height terminalHome-container">
    <v-row class="full-height">
      <v-col cols="12" class="half-height mt-12 terminal-options">
        <p class="text-center mb-12 title">
          What do you want to do ?
        </p>
        <v-btn
          color="primary"
          block
          class="quarter-height btn-replenish"
          to="terminal/replenish"
        >
          Replenish Card
        </v-btn>
        <v-btn
          color="primary"
          block
          outlined
          class="quarter-height mt-12 btn-replenish"
          to="/"
        >
          Back
        </v-btn>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
export default {};
</script>

<style lang="scss">
@import '../../assets/scss/variables.scss';
@import '../../assets/scss/common.scss';

.terminalHome-container {
  .terminal-options {
    padding-left: 30%;
    padding-right: 30%;

    .title {
      color: $accentColor;
      font-family: $mainFont !important;
      font-size: 2.5rem !important;
    }

    .btn-replenish {
      font-size: 1.3rem;
    }
  }
}
</style>
