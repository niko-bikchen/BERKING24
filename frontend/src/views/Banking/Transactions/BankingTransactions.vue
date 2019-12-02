<template>
  <v-row
    v-if="
      !processes.fetchTransactions.active && !processes.fetchTransactions.failed
    "
  >
    <v-col cols="12" v-for="(transaction, index) in transactions" :key="index">
      <app-transaction :transaction_data="transaction"></app-transaction>
    </v-col>
    <v-col cols="12">
      <v-dialog
        v-model="showMakeTransactionDialog"
        persistent
        max-width="800px"
      >
        <template v-slot:activator="{ on }">
          <v-btn block color="primary" dark v-on="on" v-if="cards.length > 0"
            >Make Transaction</v-btn
          >
          <div class="text-center" v-if="cards.length == 0">
            <v-alert type="info">
              To make a transaction you need at least one card created.
            </v-alert>
          </div>
        </template>
        <v-card>
          <v-card-title>
            <span class="headline">Make Transaction</span>
          </v-card-title>
          <v-card-text>
            <v-stepper v-model="stepNum">
              <v-stepper-header>
                <v-stepper-step :complete="stepNum > 1" step="1"
                  >Sender card</v-stepper-step
                >

                <v-divider></v-divider>

                <v-stepper-step :complete="stepNum > 3" step="2"
                  >Money and description</v-stepper-step
                >

                <v-divider></v-divider>

                <v-stepper-step :complete="stepNum > 2" step="3"
                  >Receiver card</v-stepper-step
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
                        <v-subheader
                          >Pick a card to draw money from</v-subheader
                        >
                        <v-list-item-group
                          v-model="sender_card_num"
                          color="primary"
                        >
                          <v-list-item
                            v-for="(card, index) in cards"
                            :key="index"
                          >
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
                      <v-btn color="primary darken-1" @click="stepNum = 2"
                        >Confirm</v-btn
                      >
                      <v-btn
                        color="primary darken-1"
                        outlined
                        @click="showMakeTransactionDialog = false"
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
                                label="Amount of money"
                                type="number"
                                required
                                :rules="inputValid.money.rules"
                                v-model="transaction.data.sum"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-col cols="12">
                            <v-textarea
                              auto-grow
                              solo
                              outlined
                              label="Description (optional)"
                              v-model="transaction.data.description"
                            ></v-textarea>
                          </v-col>
                          <v-slide-x-transition>
                            <v-col
                              cols="12"
                              v-if="!inputValid.sender_balance.isValid"
                            >
                              <v-alert type="error">
                                Your previosly selected card doesn't have enough
                                money for the transaction.
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
                      <v-btn text @click="stepNum = 1">Back</v-btn>
                    </v-card-actions>
                  </v-card>
                </v-stepper-content>

                <v-stepper-content step="3">
                  <v-card>
                    <v-card-text>
                      <v-container>
                        <v-row>
                          <v-col cols="12">
                            <v-form v-model="inputValid.card.isValid">
                              <v-text-field
                                label="Receiver card number"
                                type="text"
                                required
                                :rules="inputValid.card.rules"
                                :counter="16"
                                v-model="transaction.data.receiver_card"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-slide-x-transition>
                            <v-col
                              cols="12"
                              v-if="!transaction.cards.areUnequal"
                            >
                              <v-alert type="error">
                                Sender and receiver cards cannot be equal.
                              </v-alert>
                            </v-col>
                          </v-slide-x-transition>
                        </v-row>
                      </v-container>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn
                        color="primary"
                        @click="checkIfCardsEqual"
                        :disabled="!transaction.cards.areUnequal"
                      >
                        Continue
                      </v-btn>
                      <v-btn text @click="stepNum = 2">Back</v-btn>
                    </v-card-actions>
                  </v-card>
                </v-stepper-content>

                <v-stepper-content step="4">
                  <v-card>
                    <v-card-text>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Sender card:
                        </span>
                        <span
                          class="subtitle-1"
                          v-if="!processes.transaction.good"
                        >
                          {{
                            cards[sender_card_num]
                              ? cards[sender_card_num].card_number
                              : 'Cannot get card number'
                          }}
                        </span>
                      </p>
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
                        @click="stepNum = 3"
                        :disabled="
                          processes.transaction.good ||
                            processes.transaction.active
                        "
                        >Back</v-btn
                      >
                    </v-card-actions>
                  </v-card>
                </v-stepper-content>
              </v-stepper-items>
            </v-stepper>
          </v-card-text>
        </v-card>
      </v-dialog>
    </v-col>
  </v-row>
  <v-row dense v-else-if="processes.fetchTransactions.active">
    <v-col cols="12">
      <v-alert type="info">
        Fetching transactions from the server. Please wait.
        <div class="text-right mt-2">
          <v-progress-circular
            indeterminate
            color="white"
          ></v-progress-circular>
        </div>
      </v-alert>
    </v-col>
  </v-row>
  <v-row dense v-else-if="processes.fetchTransactions.failed">
    <v-col cols="12">
      <v-alert type="error">
        Failed to fetch transactions from the server.
      </v-alert>
    </v-col>
  </v-row>
</template>

<script>
import Transaction from './Transaction.vue';
import REQUEST_STATUSES from '../../../assets/js/vars';

export default {
  components: {
    appTransaction: Transaction,
  },
  data() {
    return {
      showMakeTransactionDialog: false,
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
        sender_balance: {
          isValid: true,
        },
      },
      transaction: {
        data: {
          receiver_card: '',
          sender_card: '',
          sum: '',
          description: '',
          target_endpoint: '/api/make_transaction',
        },
        cards: {
          areUnequal: true,
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
        fetchTransactions: {
          active: false,
          failed: false,
          details: '',
        },
        fetchCards: {
          active: false,
          failed: false,
          details: '',
        },
      },
      sender_card_num: 0,
    };
  },
  methods: {
    makeTransaction() {
      this.processes.transaction.active = true;

      this.transaction.data.sender_card = this.cards[
        this.sender_card_num
      ].card_number;

      let today = new Date();
      const dd = String(today.getDate()).padStart(2, '0');
      const mm = String(today.getMonth() + 1).padStart(2, '0');
      const yyyy = today.getFullYear();
      const H = today.getHours();
      const M = today.getMinutes();
      const S = today.getSeconds();
      const day = ['Mon', 'Tue', 'Wed', 'Thur', 'Fri', 'Sat', 'Sun'][
        today.getDay()
      ];
      today = `${day} ${dd}.${mm}.${yyyy} ${H}:${M}:${S}`;

      this.transaction.data.date = today;

      this.$store
        .dispatch(
          'performTransaction',
          Object.assign({}, this.transaction.data)
        )
        .then(
          requestStatus => {
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
                this.showMakeTransactionDialog = false;
                this.processes.transaction.good = false;
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
            this.processes.transaction.good = false;
            this.processes.transaction.failed = true;
            this.processes.transaction.details = requestStatus.details;
            this.processes.transaction.error = requestStatus.error;
          }
        );
    },
    checkBalance() {
      if (
        parseFloat(this.cards[this.sender_card_num].card_balance) >=
        this.transaction.data.sum
      ) {
        this.inputValid.sender_balance.isValid = true;
        this.stepNum = 3;
      } else {
        this.inputValid.sender_balance.isValid = false;
      }
    },
    checkIfCardsEqual() {
      if (
        this.cards[this.sender_card_num].card_number ===
        this.transaction.data.receiver_card
      ) {
        this.transaction.cards.areUnequal = false;
      } else {
        this.transaction.cards.areUnequal = true;
        this.stepNum = 4;
      }
    },
  },
  computed: {
    cards() {
      return this.$store.getters.getCards;
    },
    transactions() {
      const transact = this.$store.getters.getTransactions;
      return transact.reverse();
    },
  },
  beforeRouteEnter(to, from, next) {
    next(vm => {
      const comp = vm;

      comp.processes.fetchTransactions.active = true;

      comp.$store.dispatch('fetchTransactions').then(
        requestStatus => {
          comp.processes.fetchTransactions.active = false;
          comp.processes.fetchTransactions.failed = false;
          comp.processes.fetchTransactions.details = requestStatus.details;
        },
        requestStatus => {
          comp.processes.fetchTransactions.active = false;
          comp.processes.fetchTransactions.failed = true;
          comp.processes.fetchTransactions.details = requestStatus.details;
        }
      );
    });
  },
};
</script>
