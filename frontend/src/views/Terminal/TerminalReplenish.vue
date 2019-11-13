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
          <v-form v-model="inputValid.card.isValid">
            <v-text-field
              :rules="inputValid.card.rules"
              outlined
              :counter="16"
              single-line
              label="Card Number"
              v-model="transaction.data.receiver_card"
            >
            </v-text-field>
          </v-form>
          <v-btn
            color="primary"
            @click="stepNum = 2"
            class="mr-3"
            :disabled="!inputValid.card.isValid"
          >
            Continue
          </v-btn>
          <v-btn color="primary" outlined to="/terminal">Cancel</v-btn>
        </v-stepper-content>

        <v-stepper-content step="2">
          <v-form v-model="inputValid.money.isValid">
            <v-text-field
              outlined
              single-line
              label="Amount of money"
              :rules="inputValid.money.rules"
              v-model="transaction.data.sum"
            ></v-text-field>
          </v-form>
          <v-textarea
            auto-grow
            solo
            outlined
            label="Payment description (optional)"
            v-model="transaction.data.description"
          ></v-textarea>
          <v-btn
            color="primary"
            @click="stepNum = 3"
            class="mr-3"
            :disabled="!inputValid.money.isValid"
          >
            Continue
          </v-btn>
          <v-btn color="primary" outlined @click="stepNum = 1">Back</v-btn>
        </v-stepper-content>

        <v-stepper-content step="3">
          <v-card>
            <v-card-text>
              <p class="text--primary">
                <span class="font-weight-medium title">
                  Receiver card:
                </span>
                <span class="subtitle-1">
                  {{ transaction.data.receiver_card }}
                </span>
              </p>
              <p class="text--primary">
                <span class="font-weight-medium title">
                  Sum:
                </span>
                <span class="subtitle-1">
                  {{ transaction.data.sum }}
                </span>
              </p>
              <p
                class="text--primary"
                v-if="transaction.data.description != ''"
              >
                <span class="font-weight-medium title">
                  Description:
                </span>
                <br />
                <span class="body-1">
                  {{ transaction.data.description }}
                </span>
              </p>
              <v-scroll-x-transition>
                <p v-if="processes.transaction.failed">
                  <v-alert dense outlined type="error">
                    {{ processes.transaction.details }}
                  </v-alert>
                </p>
              </v-scroll-x-transition>
            </v-card-text>
            <v-card-actions>
              <v-btn color="primary" @click="makeTransaction">
                Submit
              </v-btn>
              <v-btn text @click="stepNum = 2">Back</v-btn>
            </v-card-actions>
          </v-card>
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
      inputValid: {
        card: {
          isValid: true,
          rules: [
            v => (v && /^[0-9]+$/.test(v)) || 'Card must contain digits only',
            v => (v && v.length === 16) || 'Card must be 16 numbers long',
          ],
        },
        money: {
          isValid: true,
          rules: [
            v =>
              v > 0 ||
              'The amount of oney to send cannot be less than 0 or equal to 0',
          ],
        },
      },
      transaction: {
        data: {
          receiver_card: '',
          sum: '',
          description: '',
          target_endpoint: '/api/terminal',
        },
      },
    };
  },
  methods: {
    makeTransaction() {
      this.$store.dispatch(
        'performTransaction',
        Object.assign({}, this.transaction.data)
      );

      this.transaction.data.receiver_card = '';
      this.transaction.data.sum = '';
      this.transaction.data.description = '';
    },
  },
};
</script>

<style lang="scss">
.terminalReplenish-container {
  padding-left: 15%;
  padding-right: 15%;
}
</style>
