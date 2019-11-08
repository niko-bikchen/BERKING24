<template>
  <v-card>
    <v-card-title>
      {{ card_data.card_name }}
    </v-card-title>
    <v-card-text>
      <p class="text--primary subtitle-1">
        Card number:
        <span class="font-weight-medium">
          {{ card_data.card_number }}
        </span>
      </p>
      <p class="text--primary subtitle-1">
        Balance:
        <span class="font-weight-medium">
          {{ card_data.card_balance }}
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