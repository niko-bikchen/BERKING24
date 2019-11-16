<template>
  <v-card otlined class="user-card">
    <v-card-title
      v-if="card_data.hasOwnProperty('card_name') && card_data.card_name !== ''"
    >
      {{ card_data.card_name }}
    </v-card-title>
    <v-card-text>
      <p class="text--primary subtitle-1">
        Card number:
        <span class="font-weight-medium">
          {{ card_data.card_number | formatCardNum }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Balance:
        <span class="font-weight-medium">
          {{ card_data.card_balance }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Expiration date:
        <span class="font-weight-medium">
          {{ card_data.card_expiration }}
        </span>
      </p>
    </v-card-text>
  </v-card>
</template>

<script>
export default {
  props: {
    card_data: {
      type: Object,
      required: true,
    },
  },
};
</script>

<style lang="scss">
@import '../../../assets/scss/variables.scss';
@import '../../../assets/scss/common.scss';

.user-card {
  border: 1px solid $accentColor !important;
}
</style>
