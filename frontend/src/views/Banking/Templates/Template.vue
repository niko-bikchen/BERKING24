<template>
  <v-card outlined class="user-template">
    <v-card-text>
      <p class="text--primary subtitle-1">
        Sender:
        <span class="font-weight-medium">
          {{ template_data.sender_card | formatCardNumWithMask }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Receiver:
        <span class="font-weight-medium">
          {{ template_data.receiver_card | formatCardNumWithMask }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Sum:
        <span class="font-weight-medium">
          {{ template_data.sum }}
        </span>
      </p>
      <v-expansion-panels v-if="template_data.description != ''">
        <v-expansion-panel>
          <v-expansion-panel-header class="font-weight-medium"
            >Description</v-expansion-panel-header
          >
          <v-expansion-panel-content>
            {{ template_data.description }}
          </v-expansion-panel-content>
        </v-expansion-panel>
      </v-expansion-panels>
    </v-card-text>
    <v-card-actions>
      <v-dialog v-model="showDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn color="primary" dark v-on="on">Make Transaction</v-btn>
        </template>
        <v-card>
          <v-card-title class="headline">
            Transaction summary
          </v-card-title>
          <v-card-text>
            <span class="text--primary">
              <span class="font-weight-medium title">
                Sender card:
              </span>
              <span class="subtitle-1">
                {{ template_data.sender_card }}
              </span>
            </span>
            <span class="text--primary">
              <span class="font-weight-medium title">
                Receiver card:
              </span>
              <span class="subtitle-1">
                {{ template_data.receiver_card }}
              </span>
            </span>
            <br />
            <span class="text--primary">
              <span class="font-weight-medium title">
                Sum:
              </span>
              <span class="subtitle-1">
                {{ template_data.sum }}
              </span>
            </span>
            <br />
            <span class="text--primary">
              <span class="font-weight-medium title">
                Description:
              </span>
              <br />
              <span class="body-1">
                {{ template_data.description }}
              </span>
            </span>
            <v-scroll-x-transition>
              <p v-if="processes.transaction.failed">
                <v-alert dense outlined type="error">
                  {{ processes.transaction.details }}
                </v-alert>
              </p>
            </v-scroll-x-transition>
            <v-scroll-x-transition>
              <p v-if="!balanceIsValid">
                <v-alert dense outlined type="error">
                  Not enough money on the card to perform the transaction.
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
          </v-card-text>
          <v-card-actions>
            <v-btn
              color="primary"
              @click="performTransaction"
              :loading="processes.transaction.active"
            >
              Submit
            </v-btn>
            <v-btn text @click="showDialog = false">Cancel</v-btn>
          </v-card-actions>
        </v-card>
      </v-dialog>
    </v-card-actions>
  </v-card>
</template>

<script>
export default {
  data() {
    return {
      showDialog: false,
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
      balanceIsValid: true,
    };
  },
  props: {
    template_data: {
      type: Object,
      required: true,
    },
  },
  computed: {
    cards() {
      return this.$store.getters.getCards;
    },
  },
  methods: {
    performTransaction() {
      for (let i = 0; i < this.cards.lengthl; i += 1) {
        if (this.cards[i].card_number === this.template_data.sender_card) {
          if (this.cards[i].card_balance < this.template_data.sum) {
            this.balanceIsValid = false;
            break;
          }
        }
      }

      if (this.balanceIsValid) {
        const transactionData = Object.assign({}, this.template_data);
        transactionData.target_endpoint = '/api/make_transaction';

        this.$store
          .dispatch('performTransaction', Object.assign({}, transactionData))
          .then(
            requestStatus => {
              this.processes.transaction.active = false;
              this.processes.transaction.bad = false;
              this.processes.transaction.failed = false;
              this.processes.transaction.good = true;
              this.processes.transaction.details = requestStatus.details;

              setTimeout(() => {
                this.showDialog = false;
                this.processes.transactions.good = false;
              }, 1000);
            },
            requestStatus => {
              this.processes.transaction.bad = false;
              this.processes.transaction.active = false;
              this.processes.transaction.failed = true;
              this.processes.transaction.details = requestStatus.details;
              this.processes.transaction.error = requestStatus.error;
            }
          );
      }
    },
  },
};
</script>

<style lang="scss">
@import '../../../assets/scss/variables.scss';
@import '../../../assets/scss/common.scss';

.user-template {
  border: 1px solid $accentColor !important;
}
</style>
