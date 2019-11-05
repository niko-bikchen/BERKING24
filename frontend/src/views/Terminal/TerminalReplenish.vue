<template>
  <v-container class="terminalReplenish-container">
    <v-stepper v-model="e1">
      <v-stepper-header>
        <v-stepper-step :complete="e1 > 1" step="1">
          Card number
        </v-stepper-step>

        <v-divider></v-divider>

        <v-stepper-step :complete="e1 > 2" step="2">
          Money and description
        </v-stepper-step>

        <v-divider></v-divider>

        <v-stepper-step :complete="e1 > 3" step="3">
          Payment validation
        </v-stepper-step>
      </v-stepper-header>

      <v-stepper-items>
        <v-stepper-content step="1">
          <v-text-field outlined single-line label="Card Number">
          </v-text-field>
          <v-btn color="primary" @click="e1 = 2" class="mr-3">
            Continue
          </v-btn>
          <v-btn color="primary" outlined to="/terminal">Cancel</v-btn>
        </v-stepper-content>

        <v-stepper-content step="2">
          <v-text-field
            outlined
            single-line
            label="Amount of money"
          ></v-text-field>
          <v-textarea
            auto-grow
            solo
            outlined
            label="Payment description (optional)"
          ></v-textarea>
          <v-btn color="primary" @click="e1 = 3" class="mr-3">
            Continue
          </v-btn>
          <v-btn color="primary" outlined @click="e1 = 1">Back</v-btn>
        </v-stepper-content>

        <v-stepper-content step="3">
          <h2>Receiver</h2>
          <h3>Money</h3>
          <p>
            Other details
          </p>
          <v-btn color="primary" @click="e1 = 1" class="mr-3">
            Confirm
          </v-btn>
          <v-btn color="primary" outlined @click="e1 = 2">Back</v-btn>
        </v-stepper-content>
      </v-stepper-items>
    </v-stepper>
  </v-container>
</template>

<script>
export default {
  data() {
    return {
      e1: 0,
    };
  },
};
</script>

<style lang="scss">
.terminalReplenish-container {
  padding-left: 15%;
  padding-right: 15%;
}
</style>
