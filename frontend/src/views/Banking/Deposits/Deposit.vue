<template>
  <v-card otlined class="user-deposit">
    <v-card-text>
      <p
        class="text--primary subtitle-1"
        v-if="deposit_data && deposit_data.card_num"
      >
        Card number:
        <span class="font-weight-medium">
          {{ deposit_data.card_num | formatCardNum }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Balance:
        <span class="font-weight-medium">
          {{ deposit_data.init_sum }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Start date:
        <span class="font-weight-medium">
          {{ deposit_data.start_date }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Expiration date:
        <span class="font-weight-medium">
          {{ deposit_data.end_date }}
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
