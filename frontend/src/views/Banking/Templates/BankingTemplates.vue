<template>
  <v-row
    v-if="
      !processes.fetchTemplates.active &&
        !processes.fetchCards.active &&
        !processes.fetchTemplates.failed &&
        !processes.fetchCards.failed
    "
  >
    <v-col cols="12" v-for="(template, index) in templates" :key="index">
      <app-template :template_data="template.data"></app-template>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showCreationDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn block color="primary" dark v-on="on" v-if="cards.length > 0"
            >Create Template</v-btn
          >
          <div class="text-center" v-if="cards.length == 0">
            <v-alert type="info">
              To create a template you need at least one card created.
            </v-alert>
          </div>
        </template>
        <v-card>
          <v-card-title>
            <span class="headline">Create a Template</span>
          </v-card-title>
          <v-card-text>
            <v-stepper v-model="formStep">
              <v-stepper-header>
                <v-stepper-step :complete="formStep > 1" step="1"
                  >Sender card</v-stepper-step
                >

                <v-stepper-step :complete="formStep > 2" step="1"
                  >Receiver card</v-stepper-step
                >

                <v-divider></v-divider>

                <v-stepper-step :complete="formStep > 3" step="2"
                  >Money and description</v-stepper-step
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
                      <v-btn color="primary darken-1" @click="formStep = 2"
                        >Confirm</v-btn
                      >
                      <v-btn
                        color="primary darken-1"
                        outlined
                        @click="showCreationDialog = false"
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
                                v-model="template.data.sum"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-col cols="12">
                            <v-textarea
                              auto-grow
                              solo
                              outlined
                              label="Description (optional)"
                              v-model="template.data.description"
                            ></v-textarea>
                          </v-col>
                          <v-slide-x-transition>
                            <v-col
                              cols="12"
                              v-if="!inputValid.sender_balance.isValid"
                            >
                              <v-alert type="error">
                                Your previosly selected card doesn't have enough
                                money for the template.
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
                  <v-card height="200px">
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
                                v-model="template.data.receiver_card"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-slide-x-transition>
                            <v-col cols="12" v-if="!template.cards.areUnequal">
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
                        :disabled="!inputValid.card.isValid"
                      >
                        Continue
                      </v-btn>
                      <v-btn text @click="formStep = 2">Back</v-btn>
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
                          {{ template.data.sender_card }}
                        </span>
                      </p>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Receiver card:
                        </span>
                        <span class="subtitle-1">
                          {{ template.data.receiver_card }}
                        </span>
                      </p>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Sum:
                        </span>
                        <span class="subtitle-1">
                          {{ template.data.sum }}
                        </span>
                      </p>
                      <p
                        class="text--primary"
                        v-if="template.data.description != ''"
                      >
                        <span class="font-weight-medium title">
                          Description:
                        </span>
                        <br />
                        <span class="body-1">
                          {{ template.data.description }}
                        </span>
                      </p>
                      <v-scroll-x-transition>
                        <p v-if="processes.creating_template.failed">
                          <v-alert dense outlined type="error">
                            {{ processes.creating_template.details }}
                          </v-alert>
                        </p>
                      </v-scroll-x-transition>
                      <v-scroll-x-transition>
                        <p v-if="processes.creating_template.good">
                          <v-alert dense outlined type="success">
                            {{ processes.creating_template.details }}
                          </v-alert>
                        </p>
                      </v-scroll-x-transition>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn color="primary" @click="addTemplate">
                        Submit
                      </v-btn>
                      <v-btn text @click="formStep = 3">Back</v-btn>
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
  <v-row
    dense
    v-else-if="processes.fetchCards.active || processes.fetchTemplates.active"
  >
    <v-col cols="12">
      <v-alert type="info">
        Fetching cards and templates from the server. Please wait.
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
    v-else-if="processes.fetchCards.failed || processes.fetchTemplates.failed"
  >
    <v-col cols="12">
      <v-alert type="error">
        Failed to fetch cards and templates from the server.
      </v-alert>
    </v-col>
  </v-row>
</template>

<script>
import Template from './Template.vue';

export default {
  components: {
    appTemplate: Template,
  },
  data() {
    return {
      templates: [],
      cards: [],
      showCreationDialog: false,
      formStep: 0,
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
        sender_balance: '',
      },
      template: {
        data: {
          sender_card: '',
          receiver_card: '',
          sum: '',
          description: '',
        },
        cards: {
          areUnequal: true,
        },
      },
      processes: {
        creating_template: {
          active: false,
          bad: false,
          good: false,
          failed: false,
          details: '',
          error: '',
        },
        fetchTemplates: {
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
    addTemplate() {
      this.template.data.sender_card = this.cards[this.sender_card_num];
      this.processes.creating_template.active = true;

      this.$store
        .dispatch('addTemplate', Object.assign({}, this.template.data))
        .then(
          requestStatus => {
            this.processes.creating_template.active = false;
            this.processes.creating_template.bad = false;
            this.processes.creating_template.failed = false;
            this.processes.creating_template.good = true;
            this.processes.creating_template.details = requestStatus.details;

            this.template.data.receiver_card = '';
            this.template.data.sum = '';
            this.template.data.description = '';

            setTimeout(() => {
              this.showCreationDialog = false;
              this.processes.creating_template.good = false;
            }, 1000);
          },
          requestStatus => {
            this.processes.creating_template.active = false;
            this.processes.creating_template.bad = false;
            this.processes.creating_template.failed = true;
            this.processes.creating_template.good = false;
            this.processes.creating_template.error = requestStatus.error;
            this.processes.creating_template.details = requestStatus.details;
          }
        );
    },
    checkBalance() {
      if (
        this.cards[this.sender_card_num].card_balance >= this.template.data.sum
      ) {
        this.inputValid.sender_balance.isValid = true;
        this.formStep = 3;
      } else {
        this.inputValid.sender_balance.isValid = false;
      }
    },
    checkIfCardsEqual() {
      if (
        this.cards[this.sender_card_num].card_number ===
        this.template.data.receiver_card
      ) {
        this.template.cards.areUnequal = false;
      } else {
        this.template.cards.areUnequal = true;
        this.formStep = 4;
      }
    },
  },
  created() {
    this.processes.fetchCards.active = true;
    this.processes.fetchTemplates.active = true;

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

    this.$store.dispatch('fetchTemplates').then(
      templates => {
        this.processes.fetchTemplates.active = false;
        this.processes.fetchTemplates.failed = false;
        this.templates = [...templates].slice(0, 2).reverse();
      },
      requestStatus => {
        this.processes.fetchTemplates.active = false;
        this.processes.fetchTemplates.failed = true;
        this.processes.fetchTemplates.details = requestStatus.details;
      }
    );
  },
};
</script>
