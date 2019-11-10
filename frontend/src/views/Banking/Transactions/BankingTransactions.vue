<template>
  <v-row>
    <v-col cols="12" v-for="(transaction, index) in transactions" :key="index">
      <app-transaction :transaction_data="transaction"></app-transaction>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn block color="primary" dark v-on="on" v-if="cards.length > 0"
            >Make Transaction</v-btn
          >
          <div class="text-center" v-if="cards.length == 0">
            You don't have any cards to make a transaction
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
                  >Receiver card</v-stepper-step
                >

                <v-divider></v-divider>

                <v-stepper-step :complete="stepNum > 2" step="2"
                  >Money and description</v-stepper-step
                >

                <v-divider></v-divider>

                <v-stepper-step step="3">Confirmation</v-stepper-step>
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
                          v-model="sender_card"
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
                            <v-form v-model="moneyIsValid">
                              <v-text-field
                                label="Amount of money"
                                type="number"
                                required
                                :rules="moneyRules"
                                v-model="transaction_data.sum"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-col cols="12">
                            <v-textarea
                              auto-grow
                              solo
                              outlined
                              label="Description (optional)"
                              v-model="transaction_data.description"
                            ></v-textarea>
                          </v-col>
                          <v-col cols="12" v-if="!balanceIsValid">
                            <div class="red--text">
                              Your previously entered card doesn't have enough
                              money for the transaction.
                            </div>
                          </v-col>
                        </v-row>
                      </v-container>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn
                        color="primary"
                        @click="checkBalance"
                        :disabled="!moneyIsValid"
                      >
                        Continue
                      </v-btn>
                      <v-btn text @click="stepNum = 1">Back</v-btn>
                    </v-card-actions>
                  </v-card>
                </v-stepper-content>

                <v-stepper-content step="3">
                  <v-card height="200px">
                    <v-card-text>
                      <v-container>
                        <v-row>
                          <v-col cols="12">
                            <v-form v-model="cardIsValid">
                              <v-text-field
                                label="Receiver card number"
                                type="text"
                                required
                                :rules="cardRules"
                                :counter="16"
                                v-model="transaction_data.receiver_card"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-col cols="12" v-if="!cardsAreUnequal">
                            <div class="red--text">
                              Sender and receiver cards cannot be equal.
                            </div>
                          </v-col>
                        </v-row>
                      </v-container>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn
                        color="primary"
                        @click="checkIfCardsEqual"
                        :disabled="!cardIsValid"
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
                        <span class="subtitle-1">
                          {{ cards[sender_card] }}
                        </span>
                      </p>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Receiver card:
                        </span>
                        <span class="subtitle-1">
                          {{ transaction_data.receiver_card }}
                        </span>
                      </p>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Sum:
                        </span>
                        <span class="subtitle-1">
                          {{ transaction_data.sum }}
                        </span>
                      </p>
                      <p
                        class="text--primary"
                        v-if="transaction_data.description != ''"
                      >
                        <span class="font-weight-medium title">
                          Description:
                        </span>
                        <br />
                        <span class="body-1">
                          {{ transaction_data.description }}
                        </span>
                      </p>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn color="primary" @click="makeTransaction">
                        Submit
                      </v-btn>
                      <v-btn text @click="stepNum = 3">Back</v-btn>
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
</template>

<script>
import Transaction from './Transaction.vue';

export default {
  components: {
    appTransaction: Transaction,
  },
  data() {
    return {
      showDialog: false,
      stepNum: 0,
      cardIsValid: true,
      cardRules: [
        v => (v && /^[0-9]+$/.test(v)) || 'Card must contain digits only',
        v => (v && v.length === 16) || 'Card must be 16 numbers long',
      ],
      moneyIsValid: true,
      moneyRules: [
        v =>
          v > 0 ||
          'The amount of oney to send cannot be less than 0 or equal to 0',
      ],
      transaction_data: {
        receiver_card: '',
        sum: '',
        description: '',
      },
      sender_card: '',
      balanceIsValid: true,
      cardsAreUnequal: true,
    };
  },
  computed: {
    transactions() {
      const transactions = this.$store.getters.getTransactions;

      return transactions.reverse();
    },
    cards() {
      return this.$store.getters.getCards;
    },
  },
  methods: {
    makeTransaction() {
      this.showDialog = false;
      this.transaction_data.sender_card = this.cards[
        this.sender_card
      ].card_number;

      this.$store.dispatch(
        'performTransaction',
        Object.assign({}, this.transaction_data)
      );

      this.transaction_data.receiver_card = '';
      this.transaction_data.sum = '';
      this.transaction_data.description = '';
    },
    checkBalance() {
      if (
        this.cards[this.sender_card].card_balance >= this.transaction_data.sum
      ) {
        this.balanceIsValid = true;
        this.stepNum = 3;
      } else {
        this.balanceIsValid = false;
      }
    },
    checkIfCardsEqual() {
      if (
        this.cards[this.sender_card].card_number ===
        this.transaction_data.receiver_card
      ) {
        this.cardsAreUnequal = false;
      } else {
        this.cardsAreUnequal = true;
        this.stepNum = 4;
      }
    },
  },
};
</script>
