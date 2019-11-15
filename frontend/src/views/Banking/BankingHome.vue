<template>
  <v-row>
    <v-col cols="6">
      <v-card raised>
        <v-card-title>
          Last Transactions
        </v-card-title>
        <v-card-text>
          <v-container>
            <v-row dense v-if="transactions.length > 0">
              <v-col
                cols="12"
                v-for="(transaction, index) in transactions"
                :key="index"
              >
                <app-transaction
                  :transaction_data="transaction"
                ></app-transaction>
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
                      size="20"
                    ></v-progress-circular>
                  </div>
                </v-alert>
              </v-col>
            </v-row>
            <v-row dense v-else-if="processes.fetchTransactions.failed">
              <v-col cols="12">
                <v-alert type="error">
                  {{ processes.fetchTransactions.details }}
                </v-alert>
              </v-col>
            </v-row>
            <v-row dense v-else-if="transactions.length === 0">
              <v-col cols="12">
                <v-alert type="info">
                  You don't have any transactions now. If you want to make one,
                  go to the
                  <router-link to="/berking/transactions" class="white--text"
                    >Transactions</router-link
                  >
                  section
                </v-alert>
              </v-col>
            </v-row>
          </v-container>
        </v-card-text>
        <v-card-actions>
          <v-btn color="primary" block to="/berking/transactions">More</v-btn>
        </v-card-actions>
      </v-card>
    </v-col>
    <v-col cols="6">
      <v-card raised>
        <v-card-title>
          Cards
        </v-card-title>
        <v-card-text>
          <v-container>
            <v-row dense v-if="cards.length > 0">
              <v-col cols="12" v-for="(card, index) in cards" :key="index">
                <app-card :card_data="card"></app-card>
              </v-col>
            </v-row>
            <v-row dense v-else-if="processes.fetchCards.active">
              <v-col cols="12">
                <v-alert type="info">
                  Fetching cards from the server. Please wait.
                  <div class="text-right mt-2">
                    <v-progress-circular
                      indeterminate
                      color="white"
                      size="20"
                    ></v-progress-circular>
                  </div>
                </v-alert>
              </v-col>
            </v-row>
            <v-row dense v-else-if="processes.fetchCards.failed">
              <v-col cols="12">
                <v-alert type="error">
                  {{ processes.fetchCards.details }}
                </v-alert>
              </v-col>
            </v-row>
            <v-row dense v-else-if="cards.length === 0">
              <v-col cols="12">
                <v-alert type="info">
                  You don't have any transactions now. If you want to make one,
                  go to the
                  <router-link to="/berking/cards" class="white--text"
                    >Cards</router-link
                  >
                  section
                </v-alert>
              </v-col>
            </v-row>
          </v-container>
        </v-card-text>
        <v-card-actions>
          <v-btn color="primary" block to="/berking/cards">More</v-btn>
        </v-card-actions>
      </v-card>
    </v-col>
  </v-row>
</template>

<script>
import Card from './Cards/Card.vue';
import Transaction from './Transactions/Transaction.vue';

export default {
  data() {
    return {
      cards: [],
      transactions: [],
      processes: {
        fetchCards: {
          active: false,
          failed: false,
          details: '',
        },
        fetchTransactions: {
          active: false,
          failed: false,
          details: '',
        },
      },
    };
  },
  components: {
    appCard: Card,
    appTransaction: Transaction,
  },
  created() {
    this.processes.fetchCards.active = true;
    this.processes.fetchTransactions.active = true;

    this.$store.dispatch('fetchCards').then(
      cards => {
        this.processes.fetchCards.active = false;
        this.processes.fetchCards.failed = false;
        this.cards = [...cards];
      },
      requestStatus => {
        this.processes.fetchCards.failed = true;
        this.processes.fetchCards.active = false;
        this.processes.fetchCards.details = requestStatus.details;
      }
    );

    this.$store.dispatch('fetchTransactions').then(
      transactions => {
        this.processes.fetchTransactions.active = false;
        this.processes.fetchTransactions.failed = false;
        this.transactions = [...transactions].slice(0, 2).reverse();
      },
      requestStatus => {
        this.processes.fetchTransactions.active = false;
        this.processes.fetchTransactions.failed = true;
        this.processes.fetchTransactions.details = requestStatus.details;
      }
    );
  },
};
</script>
