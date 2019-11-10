<template>
  <v-card outlined class="user-transaction">
    <v-card-title>
      {{ transaction_data.date }} | {{ transaction_data.time }}
    </v-card-title>
    <v-card-text>
      <p class="text--primary subtitle-1">
        Sender:
        <span class="font-weight-medium">
          {{ transaction_data.sender }}
          ({{ transaction_data.sender_card | formatCardNumWithMask }})
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Receiver:
        <span class="font-weight-medium">
          {{ transaction_data.receiver }}
          ({{ transaction_data.receiver_card | formatCardNumWithMask }})
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Sum:
        <span class="font-weight-medium">
          {{ transaction_data.sum }}
        </span>
      </p>
      <v-expansion-panels v-if="transaction_data.description != ''">
        <v-expansion-panel>
          <v-expansion-panel-header>Description</v-expansion-panel-header>
          <v-expansion-panel-content>
            {{ transaction_data.description }}
          </v-expansion-panel-content>
        </v-expansion-panel>
      </v-expansion-panels>
    </v-card-text>
  </v-card>
</template>

<script>
export default {
  props: {
    transaction_data: {
      type: Object,
      required: true,
    },
  },
};
</script>

<style lang="scss">
@import '../../../assets/scss/variables.scss';
@import '../../../assets/scss/common.scss';

.user-transaction {
  border: 1px solid $accentColor !important;
}
</style>
