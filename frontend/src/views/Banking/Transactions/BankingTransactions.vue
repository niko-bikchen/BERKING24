<template>
  <v-row>
    <v-col cols="12" v-for="(transaction, index) in transactions" :key="index">
      <app-transaction :transaction_data="transaction"></app-transaction>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn block color="primary" dark v-on="on">Make Transaction</v-btn>
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
                                v-model="transactionData.receiver_card"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                        </v-row>
                      </v-container>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn
                        color="primary"
                        @click="stepNum = 2"
                        :disabled="!cardIsValid"
                      >
                        Continue
                      </v-btn>
                      <v-btn text @click="showDialog = false">Cancel</v-btn>
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
                                v-model="transactionData.sum"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-col cols="12">
                            <v-textarea
                              auto-grow
                              solo
                              outlined
                              label="Description (optional)"
                              v-model="transactionData.description"
                            ></v-textarea>
                          </v-col>
                        </v-row>
                      </v-container>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn
                        color="primary"
                        @click="stepNum = 3"
                        :disabled="!moneyIsValid"
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
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Receiver card:
                        </span>
                        <span class="subtitle-1">
                          {{ transactionData.receiver_card }}
                        </span>
                      </p>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Sum:
                        </span>
                        <span class="subtitle-1">
                          {{ transactionData.sum }}
                        </span>
                      </p>
                      <p
                        class="text--primary"
                        v-if="transactionData.description != ''"
                      >
                        <span class="font-weight-medium title">
                          Description:
                        </span>
                        <br />
                        <span class="body-1">
                          {{ transactionData.description }}
                        </span>
                      </p>
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
        v => (v && v.match(/^[0-9]+$/)) || 'Card must contain digits only',
        v => (v && v.length === 16) || 'Card must be 16 numbers long',
      ],
      moneyIsValid: true,
      moneyRules: [
        v =>
          v > 0 ||
          'The amount of oney to send cannot be less than 0 or equal to 0',
      ],
      transactionData: {
        receiver_card: '',
        sum: '',
        description: '',
      },
    };
  },
  computed: {
    transactions() {
      const transactions = this.$store.getters.getTransactions;

      return transactions.reverse();
    },
  },
  methods: {
    makeTransaction() {
      this.showDialog = false;
      this.$store.dispatch('performTransaction', this.transactionData);
    },
  },
};
</script>
