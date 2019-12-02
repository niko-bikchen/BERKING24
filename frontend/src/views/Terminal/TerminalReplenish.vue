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
              type="number"
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
                  {{ transaction.data.receiver_card | formatCardNum }}
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
              <v-scroll-x-transition>
                <p v-if="processes.transaction.good">
                  <v-alert dense outlined type="success">
                    {{ processes.transaction.details }}
                  </v-alert>
                </p>
              </v-scroll-x-transition>
              <v-scroll-x-transition>
                <p v-if="processes.transaction.bad">
                  <v-alert dense outlined type="error">
                    {{ processes.transaction.details }}
                  </v-alert>
                </p>
              </v-scroll-x-transition>
            </v-card-text>
            <v-card-actions>
              <v-btn
                color="primary"
                @click="makeTransaction"
                :loading="processes.transaction.active"
                :disabled="processes.transaction.good"
              >
                Submit
              </v-btn>
              <v-btn
                text
                @click="stepNum = 2"
                :disabled="
                  processes.transaction.good || processes.transaction.active
                "
                >Back</v-btn
              >
            </v-card-actions>
          </v-card>
        </v-stepper-content>
      </v-stepper-items>
    </v-stepper>
  </v-container>
</template>

<script>
import REQUEST_STATUSES from '../../assets/js/vars';

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
      processes: {
        transaction: {
          active: false,
          bad: false,
          good: false,
          failed: false,
          details: '',
          error: '',
        },
      },
    };
  },
  methods: {
    makeTransaction() {
      this.processes.transaction.active = true;

      this.$store
        .dispatch(
          'performTransaction',
          Object.assign({}, this.transaction.data)
        )
        .then(
          requestStatus => {
            console.log(requestStatus);

            if (requestStatus.status === REQUEST_STATUSES().finished.pos) {
              this.processes.transaction.active = false;
              this.processes.transaction.bad = false;
              this.processes.transaction.failed = false;
              this.processes.transaction.good = true;
              this.processes.transaction.details = requestStatus.details;

              this.transaction.data.receiver_card = '';
              this.transaction.data.sum = '';
              this.transaction.data.description = '';

              setTimeout(() => {
                this.processes.transaction.good = false;
                this.$router.push({ path: '/terminal' });
              }, 1000);
            } else {
              this.processes.transaction.active = false;
              this.processes.transaction.bad = true;
              this.processes.transaction.failed = false;
              this.processes.transaction.good = false;
              this.processes.transaction.details = requestStatus.details;
            }
          },
          requestStatus => {
            this.processes.transaction.bad = false;
            this.processes.transaction.active = false;
            this.processes.transaction.failed = true;
            this.processes.transaction.details = requestStatus.details;
            this.processes.transaction.error = requestStatus.error;
          }
        );
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
