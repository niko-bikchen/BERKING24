<template>
  <v-row>
    <v-col rows="12" class="text-center">
      <h2 class="cards-counter">You have {{ cards.length }} / 10 cards</h2>
    </v-col>
    <v-col cols="12" v-for="(card, index) in cards" :key="index">
      <app-card :card_data="card"></app-card>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn block color="primary" dark v-on="on">Add Card</v-btn>
        </template>
        <v-card>
          <v-card-title>
            <span class="headline">Create a Card</span>
          </v-card-title>
          <v-card-text>
            <v-container>
              <v-row>
                <v-col cols="12">
                  <v-text-field
                    label="Card name (optional)"
                    type="text"
                    required
                    v-model="newCardData.card_name"
                  ></v-text-field>
                </v-col>
              </v-row>
            </v-container>
          </v-card-text>
          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn color="blue darken-1" text @click="showDialog = false"
              >Close</v-btn
            >
            <v-btn
              color="blue darken-1"
              text
              @click="createCard"
              :loading="requestInProcess"
              >Submit</v-btn
            >
          </v-card-actions>
        </v-card>
      </v-dialog>
    </v-col>
  </v-row>
</template>

<script>
import Card from './Card.vue';

export default {
  components: {
    appCard: Card,
  },
  data() {
    return {
      showDialog: false,
      newCardData: {
        card_name: '',
      },
    };
  },
  computed: {
    cards() {
      return this.$store.getters.getCards;
    },
    requestInProcess() {
      return this.$store.getters.getRequestStatus;
    },
  },
  methods: {
    createCard() {
      console.log(this.$store.getters.getUserData);

      this.newCardData.user_email = this.$store.getters.getUserData.user_email;

      console.log(this.newCardData);

      this.$store.dispatch('addCard', this.newCardData);
      this.showDialog = this.requestInProcess;
    },
  },
};
</script>

<style lang="scss">
@import '../../../assets/scss/variables.scss';
@import '../../../assets/scss/common.scss';

.cards-counter {
  color: $accentColor;
  font-family: $mainFont;
  font-size: 2rem;
}
</style>
