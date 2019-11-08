<template>
  <v-row>
    <v-col cols="6">
      <v-card raised>
        <v-card-title>
          Transactions
        </v-card-title>
        <v-card-text>
          <v-card tile>
            <v-card-title>
              15.02.2019 | 15:51
            </v-card-title>
            <v-card-text>
              <p class="text--primary subtitle-1">
                Sender:
                <span class="font-weight-medium">
                  Jane Doe (1132-12..)
                </span>
              </p>
              <p class="text--primary subtitle-1">
                Receiver:
                <span class="font-weight-medium">
                  John Doe (1532-14..)
                </span>
              </p>
              <p class="text--primary subtitle-1">
                Sum:
                <span class="font-weight-medium">
                  151.12
                </span>
              </p>
              <v-expansion-panels>
                <v-expansion-panel>
                  <v-expansion-panel-header
                    >Description</v-expansion-panel-header
                  >
                  <v-expansion-panel-content>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed
                    do eiusmod tempor incididunt ut labore et dolore magna
                    aliqua. Ut enim ad minim veniam, quis nostrud exercitation
                    ullamco laboris nisi ut aliquip ex ea commodo consequat.
                  </v-expansion-panel-content>
                </v-expansion-panel>
              </v-expansion-panels>
            </v-card-text>
          </v-card>
        </v-card-text>
        <v-card-actions>
          <v-btn color="primary" block to="/berking/transactions">More</v-btn>
        </v-card-actions>
      </v-card>
    </v-col>
    <v-col cols="6">
      <v-card raised>
        <v-card-title>
          Cards
        </v-card-title>
        <v-card-text>
          <v-card tile>
            <v-card-title>
              Sample Card
            </v-card-title>
            <v-card-text>
              <p class="text--primary subtitle-1">
                Card number:
                <span class="font-weight-medium">
                  1532-1532-1532-1532
                </span>
              </p>
              <p class="text--primary subtitle-1">
                Balance:
                <span class="font-weight-medium">123.123</span>
              </p>
            </v-card-text>
          </v-card>
        </v-card-text>
        <v-card-actions>
          <v-btn color="primary" block to="/berking/cards">More</v-btn>
        </v-card-actions>
      </v-card>
    </v-col>
  </v-row>
</template>

<script>
export default {};
</script>
