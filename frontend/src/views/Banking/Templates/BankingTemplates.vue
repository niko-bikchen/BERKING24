<template>
  <v-row>
    <v-col cols="12" v-for="(template, index) in templates" :key="index">
      <app-template :template_data="template"></app-template>
    </v-col>
    <v-col cols="12">
      <v-dialog v-model="showDialog" persistent max-width="600px">
        <template v-slot:activator="{ on }">
          <v-btn block color="primary" dark v-on="on">Create a Template</v-btn>
        </template>
        <v-card>
          <v-card-title>
            <span class="headline">Create a Template</span>
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
                                v-model="template_data.receiver_card"
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
                                v-model="template_data.sum"
                              ></v-text-field>
                            </v-form>
                          </v-col>
                          <v-col cols="12">
                            <v-textarea
                              auto-grow
                              solo
                              outlined
                              label="Description (optional)"
                              v-model="template_data.description"
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
                          {{ template_data.receiver_card }}
                        </span>
                      </p>
                      <p class="text--primary">
                        <span class="font-weight-medium title">
                          Sum:
                        </span>
                        <span class="subtitle-1">
                          {{ template_data.sum }}
                        </span>
                      </p>
                      <p
                        class="text--primary"
                        v-if="template_data.description != ''"
                      >
                        <span class="font-weight-medium title">
                          Description:
                        </span>
                        <br />
                        <span class="body-1">
                          {{ template_data.description }}
                        </span>
                      </p>
                    </v-card-text>
                    <v-card-actions>
                      <v-btn color="primary" @click="addTemplate">
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
import Template from './Template.vue';

export default {
  components: {
    appTemplate: Template,
  },
  computed: {
    templates() {
      return this.$store.getters.getTemplates;
    },
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
      template_data: {
        receiver_card: '',
        sum: '',
        description: '',
      },
    };
  },
  methods: {
    addTemplate() {
      this.showDialog = false;
      this.$store.dispatch(
        'addTemplate',
        Object.assign({}, this.template_data)
      );

      this.template_data.receiver_card = '';
      this.template_data.sum = '';
      this.template_data.description = '';
    },
  },
};
</script>
