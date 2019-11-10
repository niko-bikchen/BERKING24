<template>
  <v-row>
    <v-col cols="12" v-for="(deposit, index) in deposits" :key="index">
      <app-deposit :deposit_data="deposit"></app-deposit>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showDialog" persistent max-width="290px">
        <template v-slot:activator="{ on }">
          <v-btn color="primary" block v-on="on">Create Deposit</v-btn>
        </template>
        <v-card>
          <v-card-title class="headline">Pick a Card</v-card-title>
          <v-card-text>
            <v-list>
              <v-subheader>Pick a card to bind deposit to</v-subheader>
              <v-list-item-group v-model="depositCard" color="primary">
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
            <v-btn color="primary darken-1" @click="createDeposit"
              >Confirm</v-btn
            >
            <v-btn color="primary darken-1" outlined @click="showDialog = false"
              >Cancel</v-btn
            >
          </v-card-actions>
        </v-card>
      </v-dialog>
    </v-col>
  </v-row>
</template>

<script>
import Deposit from './Deposit.vue';

export default {
  data() {
    return {
      showDialog: false,
      depositCard: '',
    };
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
  },
  methods: {
    createDeposit() {
      this.showDialog = false;
      console.log(this.cards[this.depositCard]);
      // this.$store.dispatch('createDeposit');
    },
  },
};
</script>
