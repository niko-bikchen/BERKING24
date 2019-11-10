<template>
  <v-container class="terminalReplenish-container">
    <v-stepper v-model="stepNum">
      <v-stepper-header>
        <v-stepper-step :complete="stepNum > 1" step="1">
          Card number
        </v-stepper-step>

        <v-divider></v-divider>

        <v-stepper-step :complete="stepNum > 2" step="2">
          Money and description
        </v-stepper-step>

        <v-divider></v-divider>

        <v-stepper-step :complete="stepNum > 3" step="3">
          Payment validation
        </v-stepper-step>
      </v-stepper-header>

      <v-stepper-items>
        <v-stepper-content step="1">
          <v-form v-model="cardIsValid">
            <v-text-field
              :rules="cardRules"
              outlined
              :counter="16"
              single-line
              label="Card Number"
            >
            </v-text-field>
          </v-form>
          <v-btn
            color="primary"
            @click="stepNum = 2"
            class="mr-3"
            :disabled="!cardIsValid"
          >
            Continue
          </v-btn>
          <v-btn color="primary" outlined to="/terminal">Cancel</v-btn>
        </v-stepper-content>

        <v-stepper-content step="2">
          <v-form v-model="moneyIsValid">
            <v-text-field
              outlined
              single-line
              label="Amount of money"
              :rules="moneyRules"
            ></v-text-field>
          </v-form>
          <v-textarea
            auto-grow
            solo
            outlined
            label="Payment description (optional)"
          ></v-textarea>
          <v-btn
            color="primary"
            @click="stepNum = 3"
            class="mr-3"
            :disabled="!moneyIsValid"
          >
            Continue
          </v-btn>
          <v-btn color="primary" outlined @click="stepNum = 1">Back</v-btn>
        </v-stepper-content>

        <v-stepper-content step="3">
          <h2>Receiver</h2>
          <h3>Money</h3>
          <p>
            Other details
          </p>
          <v-btn color="primary" @click="stepNum = 1" class="mr-3">
            Confirm
          </v-btn>
          <v-btn color="primary" outlined @click="stepNum = 2">Back</v-btn>
        </v-stepper-content>
      </v-stepper-items>
    </v-stepper>
  </v-container>
</template>

<script>
export default {
  data() {
    return {
      stepNum: 0,
      cardIsValid: true,
      cardRules: [
        v => (v && v.match(/^[0-9]+$/)) || 'Card must contain digits only',
        v => (v && v.length === 16) || 'Card must be 16 numbers long',
      ],
      moneyIsValid: true,
      moneyRules: [
        v =>
          v > 0 ||
          'The amount of oney to send cannot be less than 0 or equal to 0',
      ],
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
