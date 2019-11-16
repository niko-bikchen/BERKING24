<template>
  <v-row v-if="!processes.fetchCards.active && !processes.fetchCards.failed">
    <v-col rows="12" class="text-center">
      <h2 class="cards-counter">You have {{ cards.length }} / 10 cards</h2>
    </v-col>
    <v-col cols="12" v-for="(card, index) in cards" :key="index">
      <app-card :card_data="card"></app-card>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showCreateCardDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn
            block
            color="primary"
            dark
            v-on="on"
            v-if="cards.length !== 10"
          >
            Add Card
          </v-btn>
          <v-alert type="info" v-else>
            You can't create more than 10 cards.
          </v-alert>
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
                    v-model="new_card.card_name"
                  ></v-text-field>
                </v-col>
                <v-scroll-x-transition>
                  <v-col cols="12" v-if="processes.create_card.failed">
                    <v-alert dense outlined type="error">
                      {{ processes.create_card.details }}
                    </v-alert>
                  </v-col>
                </v-scroll-x-transition>
                <v-scroll-x-transition>
                  <v-col cols="12" v-if="processes.create_card.good">
                    <v-alert dense outlined type="success">
                      {{ processes.create_card.details }}
                    </v-alert>
                  </v-col>
                </v-scroll-x-transition>
              </v-row>
            </v-container>
          </v-card-text>
          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn
              color="blue darken-1"
              text
              @click="showCreateCardDialog = false"
              >Close</v-btn
            >
            <v-btn
              color="blue darken-1"
              text
              :loading="processes.create_card.active"
              @click="createCard"
              >Submit</v-btn
            >
          </v-card-actions>
        </v-card>
      </v-dialog>
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
</template>

<script>
import Card from './Card.vue';

export default {
  components: {
    appCard: Card,
  },
  data() {
    return {
      showCreateCardDialog: false,
      new_card: {
        card_name: '',
      },
      processes: {
        create_card: {
          active: false,
          good: false,
          bad: false,
          failed: false,
          details: '',
          error: '',
        },
        fetchCards: {
          active: false,
          failed: false,
          details: '',
        },
      },
    };
  },
  methods: {
    createCard() {
      this.processes.create_card.active = true;

      this.$store.dispatch('addCard', this.new_card.card_name.slice(0)).then(
        requestStatus => {
          this.processes.create_card.active = false;
          this.processes.create_card.bad = false;
          this.processes.create_card.failed = false;
          this.processes.create_card.good = true;
          this.processes.create_card.details = requestStatus.details;

          this.new_card.card_name = '';

          setTimeout(() => {
            this.showCreateCardDialog = false;
            this.processes.create_card.good = false;
          }, 1000);
        },
        requestStatus => {
          this.processes.create_card.bad = false;
          this.processes.create_card.active = false;
          this.processes.create_card.failed = true;
          this.processes.create_card.details = requestStatus.details;
          this.processes.create_card.error = requestStatus.error;
        }
      );
    },
  },
  computed: {
    cards() {
      console.log(this.$store.getters.getCards);
      return this.$store.getters.getCards;
    },
  },
  beforeRouteEnter(to, from, next) {
    next(vm => {
      const comp = vm;

      comp.processes.fetchCards.active = true;

      comp.$store.dispatch('fetchCards').then(
        requestStatus => {
          comp.processes.fetchCards.active = false;
          comp.processes.fetchCards.failed = false;
          comp.processes.fetchCards.details = requestStatus.details;
        },
        requestStatus => {
          comp.processes.fetchCards.failed = true;
          comp.processes.fetchCards.active = false;
          comp.processes.fetchCards.details = requestStatus.details;
        }
      );
    });
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
