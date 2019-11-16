<template>
  <v-card otlined class="user-deposit">
    <v-card-text>
      <p class="text--primary subtitle-1">
        Card number:
        <span class="font-weight-medium">
          {{ deposit_data.card_number | formatCardNum }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Balance:
        <span class="font-weight-medium">
          {{ deposit_data.deposit_balance }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Start date:
        <span class="font-weight-medium">
          {{ deposit_data.deposit_start }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Expiration date:
        <span class="font-weight-medium">
          {{ deposit_data.deposit_expiration }}
        </span>
      </p>
    </v-card-text>
  </v-card>
</template>

<script>
export default {
  props: {
    deposit_data: {
      type: Object,
      required: true,
    },
  },
};
</script>

<style lang="scss">
@import '../../../assets/scss/variables.scss';
@import '../../../assets/scss/common.scss';

.user-deposit {
  border: 1px solid $accentColor !important;
}
</style>
