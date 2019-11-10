<template>
  <v-card outlined class="user-template">
    <v-card-text>
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
                Receiver name:
              </span>
              <span class="subtitle-1">
                Sample
              </span>
            </span>
            <br />
            <span class="text--primary">
              <span class="font-weight-medium title">
                Sum:
              </span>
              <span class="subtitle-1">
                1234
              </span>
            </span>
            <br />
            <span class="text--primary">
              <span class="font-weight-medium title">
                Description:
              </span>
              <br />
              <span class="body-1">
                1234
              </span>
            </span>
          </v-card-text>
          <v-card-actions>
            <v-btn color="primary" @click="makeTransaction">
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
    };
  },
  props: {
    template_data: {
      type: Object,
      required: true,
    },
  },
  methods: {
    makeTransaction() {
      this.showDialog = false;
      console.log(this.template_data);
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
