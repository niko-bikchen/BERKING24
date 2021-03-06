<template>
  <v-row
    v-if="
      !processes.fetchDeposits.active &&
        !processes.fetchCards.active &&
        !processes.fetchDeposits.failed &&
        !processes.fetchCards.failed
    "
  >
    <v-col cols="12" v-for="(deposit, index) in deposits" :key="index">
      <app-deposit :deposit_data="deposit"></app-deposit>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showDialog" persistent max-width="800px">
        <template v-slot:activator="{ on }">
          <v-btn
            color="primary"
            block
            v-on="on"
            v-if="cards.length > 0 && deposits.length < 1"
            >Create Deposit</v-btn
          >
          <div class="text-center" v-if="cards.length == 0">
            <v-alert type="info">
              To make make a deposit you need at least one card created.
            </v-alert>
          </div>
        </template>
        <v-stepper v-model="formStep">
          <v-stepper-header>
            <v-stepper-step :complete="formStep > 1" step="1"
              >Card to bind deposit to</v-stepper-step
            >

            <v-divider></v-divider>

            <v-stepper-step :complete="formStep > 2" step="2"
              >Initial sum</v-stepper-step
            >

            <v-divider></v-divider>

            <v-stepper-step :complete="formStep > 3" step="3"
              >End date</v-stepper-step
            >

            <v-divider></v-divider>

            <v-stepper-step step="4">Confirmation</v-stepper-step>
          </v-stepper-header>

          <v-stepper-items>
            <v-stepper-content step="1">
              <v-card>
                <v-card-title class="headline">Pick a Card</v-card-title>
                <v-card-text>
                  <v-list>
                    <v-subheader>Pick a card to bind deposit to</v-subheader>
                    <v-list-item-group
                      v-model="deposit_card_num"
                      color="primary"
                    >
                      <v-list-item v-for="(card, index) in cards" :key="index">
                        <v-list-item-content>
                          <v-list-item-title
                            v-text="card.card_number"
                          ></v-list-item-title>
                        </v-list-item-content>
                      </v-list-item>
                    </v-list-item-group>
                  </v-list>
                </v-card-text>
                <v-card-actions>
                  <v-spacer></v-spacer>
                  <v-btn color="primary darken-1" @click="formStep = 2"
                    >Confirm</v-btn
                  >
                  <v-btn
                    color="primary darken-1"
                    outlined
                    @click="showDialog = false"
                    >Cancel</v-btn
                  >
                </v-card-actions>
              </v-card>
            </v-stepper-content>

            <v-stepper-content step="2">
              <v-card>
                <v-card-text>
                  <v-container>
                    <v-row>
                      <v-col cols="12">
                        <v-form v-model="inputValid.money.isValid">
                          <v-text-field
                            label="Initial sum"
                            type="number"
                            required
                            :rules="inputValid.money.rules"
                            v-model="deposit.data.init_sum"
                          ></v-text-field>
                        </v-form>
                      </v-col>
                      <v-slide-x-transition>
                        <v-col
                          cols="12"
                          v-if="!inputValid.deposit_card_balance.isValid"
                        >
                          <v-alert type="error">
                            Your previosly selected card doesn't have enough
                            money.
                          </v-alert>
                        </v-col>
                      </v-slide-x-transition>
                    </v-row>
                  </v-container>
                </v-card-text>
                <v-card-actions>
                  <v-btn
                    color="primary"
                    @click="checkBalance"
                    :disabled="!inputValid.money.isValid"
                  >
                    Continue
                  </v-btn>
                  <v-btn text @click="formStep = 1">Back</v-btn>
                </v-card-actions>
              </v-card>
            </v-stepper-content>

            <v-stepper-content step="3">
              <v-card>
                <v-card-text>
                  <v-container>
                    <v-row justify="center">
                      <v-date-picker
                        v-model="deposit.data.end_date"
                        :min="today"
                        landscape
                        color="primary"
                      ></v-date-picker>
                      <v-col cols="12" v-if="processes.getIncome.failed">
                        <v-alert type="error"
                          >Failed to calculate income</v-alert
                        >
                      </v-col>
                    </v-row>
                  </v-container>
                </v-card-text>
                <v-card-actions>
                  <v-btn
                    color="primary"
                    :disabled="!deposit.data.end_date === ''"
                    :loading="processes.getIncome.active"
                    @click="calculateIncome"
                  >
                    Continue
                  </v-btn>
                  <v-btn
                    text
                    @click="formStep = 2"
                    :disabled="processes.getIncome.active"
                    >Back</v-btn
                  >
                </v-card-actions>
              </v-card>
            </v-stepper-content>

            <v-stepper-content step="4">
              <v-card>
                <v-card-text>
                  <p class="text--primary">
                    <span class="font-weight-medium title">
                      Card to bind deposit to:
                    </span>
                    <span
                      class="subtitle-1"
                      v-if="
                        cards[deposit_card_num] &&
                          cards[deposit_card_num].card_number
                      "
                    >
                      {{ cards[deposit_card_num].card_number | formatCardNum }}
                    </span>
                  </p>
                  <p class="text--primary">
                    <span class="font-weight-medium title">
                      Initial sum:
                    </span>
                    <span class="subtitle-1">
                      {{ deposit.data.init_sum }}
                    </span>
                  </p>
                  <p class="text--primary">
                    <span class="font-weight-medium title">
                      End date:
                    </span>
                    <span class="body-1">
                      {{
                        deposit.data.end_date
                          .split('-')
                          .reverse()
                          .join('.')
                      }}
                    </span>
                  </p>
                  <p class="text--primary">
                    <span class="font-weight-medium title">
                      Expected income:
                    </span>
                    <span class="body-1">
                      {{ this.income }}
                    </span>
                  </p>
                  <v-scroll-x-transition>
                    <p v-if="processes.create_deposit.failed">
                      <v-alert dense outlined type="error">
                        {{ processes.create_deposit.details }}
                      </v-alert>
                    </p>
                  </v-scroll-x-transition>
                  <v-scroll-x-transition>
                    <p v-if="processes.create_deposit.good">
                      <v-alert dense outlined type="success">
                        {{ processes.create_deposit.details }}
                      </v-alert>
                    </p>
                  </v-scroll-x-transition>
                </v-card-text>
                <v-card-actions>
                  <v-btn
                    color="primary"
                    @click="createDeposit"
                    :loading="processes.create_deposit.active"
                    :disabled="processes.create_deposit.good"
                  >
                    Submit
                  </v-btn>
                  <v-btn
                    text
                    @click="formStep = 3"
                    :disabled="
                      processes.create_deposit.good ||
                        processes.create_deposit.active
                    "
                    >Back</v-btn
                  >
                </v-card-actions>
              </v-card>
            </v-stepper-content>
          </v-stepper-items>
        </v-stepper>
      </v-dialog>
    </v-col>
  </v-row>
  <v-row
    dense
    v-else-if="processes.fetchCards.active || processes.fetchDeposits.active"
  >
    <v-col cols="12">
      <v-alert type="info">
        Fetching deposits from the server. Please wait.
        <div class="text-right mt-2">
          <v-progress-circular
            indeterminate
            color="white"
          ></v-progress-circular>
        </div>
      </v-alert>
    </v-col>
  </v-row>
  <v-row
    dense
    v-else-if="processes.fetchCards.failed || processes.fetchDeposits.failed"
  >
    <v-col cols="12">
      <v-alert type="error">
        Failed to fetch deposits from the server.
      </v-alert>
    </v-col>
  </v-row>
</template>

<script>
import Deposit from './Deposit.vue';

export default {
  data() {
    return {
      formStep: 0,
      showDialog: false,
      deposit_card_num: 0,
      income: 0,
      processes: {
        create_deposit: {
          active: false,
          good: false,
          bad: false,
          failed: false,
          details: '',
          error: '',
        },
        fetchDeposits: {
          active: false,
          failed: false,
          details: '',
        },
        fetchCards: {
          active: false,
          failed: false,
          details: '',
        },
        getIncome: {
          active: false,
          failed: false,
          details: '',
        },
      },
      inputValid: {
        money: {
          isValid: true,
          rules: [
            v =>
              v > 0 ||
              'The amount of oney to send cannot be less than 0 or equal to 0',
          ],
        },
        deposit_card_balance: {
          isValid: true,
        },
      },
      deposit: {
        data: {
          card_num: '',
          init_sum: 0,
          end_date: '',
        },
      },
    };
  },
  methods: {
    checkBalance() {
      if (
        parseFloat(this.cards[this.deposit_card_num].card_balance) >=
        this.deposit.data.init_sum
      ) {
        this.inputValid.deposit_card_balance.isValid = true;
        this.formStep = 3;
      } else {
        this.inputValid.deposit_card_balance.isValid = false;
      }
    },
    calculateIncome() {
      const exprirationDate = this.deposit.data.end_date
        .split('-')
        .reverse()
        .join('.');
      this.processes.getIncome.active = true;

      this.$store
        .dispatch('calculateIncome', {
          sum: this.deposit.data.init_sum,
          exp_date: exprirationDate,
        })
        .then(
          income => {
            this.processes.getIncome.active = false;
            this.income = income;
            this.formStep = 4;
          },
          requestStatus => {
            this.processes.getIncome.active = false;
            this.processes.getIncome.failed = true;
            this.processes.getIncome.details = requestStatus.details;
          }
        );
    },
    createDeposit() {
      const depositData = Object.assign({}, this.deposit.data);
      depositData.start_date = this.today
        .split('-')
        .reverse()
        .join('.');
      depositData.card_num = this.cards[this.deposit_card_num].card_number;
      depositData.end_date = this.deposit.data.end_date
        .split('-')
        .reverse()
        .join('.');

      this.processes.create_deposit.active = true;
      this.$store
        .dispatch('createDeposit', Object.assign({}, depositData))
        .then(
          requestStatus => {
            this.processes.create_deposit.active = false;
            this.processes.create_deposit.bad = false;
            this.processes.create_deposit.failed = false;
            this.processes.create_deposit.good = true;
            this.processes.create_deposit.details = requestStatus.details;

            this.deposit.data.card_num = '';
            this.deposit.data.init_sum = '';
            this.deposit.data.end_date = '';

            setTimeout(() => {
              this.showDialog = false;
              this.processes.create_deposit.good = false;
            }, 1000);
          },
          requestStatus => {
            this.processes.create_deposit.active = false;
            this.processes.create_deposit.bad = false;
            this.processes.create_deposit.failed = true;
            this.processes.create_deposit.good = false;
            this.processes.create_deposit.error = requestStatus.error;
            this.processes.create_deposit.details = requestStatus.details;
          }
        );
    },
  },
  components: {
    appDeposit: Deposit,
  },
  computed: {
    deposits() {
      return this.$store.getters.getDeposits;
    },
    cards() {
      return this.$store.getters.getCards;
    },
    today() {
      const today = new Date();
      const dd = String(today.getDate()).padStart(2, '0');
      const mm = String(today.getMonth() + 1).padStart(2, '0');
      const yyyy = today.getFullYear();

      return `${yyyy}-${mm}-${dd}`;
    },
  },
  beforeRouteEnter(to, from, next) {
    next(vm => {
      const comp = vm;

      comp.processes.fetchDeposits.active = true;

      comp.$store.dispatch('fetchDeposits').then(
        requestStatus => {
          comp.processes.fetchDeposits.active = false;
          comp.processes.fetchDeposits.failed = false;
          comp.processes.fetchDeposits.details = requestStatus.details;
        },
        requestStatus => {
          comp.processes.fetchDeposits.failed = true;
          comp.processes.fetchDeposits.active = false;
          comp.processes.fetchDeposits.details = requestStatus.details;
        }
      );
    });
  },
};
</script>
