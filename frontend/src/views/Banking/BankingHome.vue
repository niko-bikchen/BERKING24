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
            <v-row dense v-else>
              <v-col cols="12">
                <v-card>
                  <v-card-text>
                    You don't have any transactions now. If you want to make
                    one, go to the
                    <router-link to="/berking/transactions"
                      >Transactions</router-link
                    >
                    section
                  </v-card-text>
                </v-card>
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
            <v-row dense v-else>
              <v-col cols="12">
                <v-card>
                  <v-card-text>
                    You don't have any cards now. If you want to create one, go
                    to the
                    <router-link to="/berking/cards">Cards</router-link> section
                  </v-card-text>
                </v-card>
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
  components: {
    appCard: Card,
    appTransaction: Transaction,
  },
  computed: {
    cards() {
      const cards = this.$store.getters.getCards;

      return cards.slice(0, 2);
    },
    transactions() {
      const transactions = this.$store.getters.getTransactions;

      return transactions.slice(0, 2).reverse();
    },
  },
};
</script>
