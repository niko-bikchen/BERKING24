<template>
  <v-app class="app-banking">
    <v-navigation-drawer v-model="showDrawer" app clipped>
      <v-list nav>
        <v-subheader>What do you want to see ?</v-subheader>
        <v-list-item-group>
          <v-list-item exact to="/berking">
            <v-list-item-content>
              <v-list-item-title>Home</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/cards">
            <v-list-item-content>
              <v-list-item-title>Cards</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/transactions">
            <v-list-item-content>
              <v-list-item-title>Transactions</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/templates">
            <v-list-item-content>
              <v-list-item-title>Templates</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/deposits">
            <v-list-item-content>
              <v-list-item-title>Deposits</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
        </v-list-item-group>
      </v-list>
    </v-navigation-drawer>
    <v-app-bar app flat clipped-left>
      <v-container fluid>
        <v-row no-gutters align="baseline">
          <v-col cols="4">
            <v-app-bar-nav-icon @click.stop="showDrawer = !showDrawer">
            </v-app-bar-nav-icon>
          </v-col>
          <v-col cols="4" class="text-center">
            <v-toolbar-title>
              Berking
            </v-toolbar-title>
          </v-col>
          <v-col cols="4" class="text-right">
            <v-dialog v-model="showDialog" persistent max-width="600px">
              <template v-slot:activator="{ on }">
                <v-btn color="primary" dark v-on="on">Sign Up/In</v-btn>
              </template>
              <v-card>
                <v-card-title>Sign In</v-card-title>
                <v-card-text>
                  <v-container>
                    <v-row>
                      <v-col cols="12">
                        <v-text-field
                          label="Email*"
                          type="email"
                          required
                        ></v-text-field>
                      </v-col>
                      <v-col cols="12">
                        <v-text-field
                          label="Password*"
                          type="password"
                          required
                        ></v-text-field>
                      </v-col>
                      <v-col cold="12">
                        <v-dialog
                          v-model="showDialog1"
                          persistent
                          max-width="600px"
                        >
                          <template v-slot:activator="{ on }">
                            First time here ?
                            <v-btn text x-small v-on="on">Sign Up</v-btn>
                          </template>
                          <v-card>
                            <v-card-title>
                              <span class="headline">Sign Up</span>
                            </v-card-title>
                            <v-card-text>
                              <v-container>
                                <v-row>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-text-field
                                      label="Legal first name*"
                                      required
                                    ></v-text-field>
                                  </v-col>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-text-field
                                      label="Legal middle name"
                                    ></v-text-field>
                                  </v-col>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-text-field
                                      label="Legal last name*"
                                      required
                                    ></v-text-field>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-text-field
                                      label="Email*"
                                      type="email"
                                      required
                                    ></v-text-field>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-text-field
                                      label="Password*"
                                      type="password"
                                      required
                                    ></v-text-field>
                                  </v-col>
                                </v-row>
                              </v-container>
                              <small>*indicates required field</small>
                            </v-card-text>
                            <v-card-actions>
                              <v-spacer></v-spacer>
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="showDialog = showDialog1 = false"
                                >Close</v-btn
                              >
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="showDialog = showDialog1 = false"
                                >Submit</v-btn
                              >
                            </v-card-actions>
                          </v-card>
                        </v-dialog>
                      </v-col>
                    </v-row>
                  </v-container>
                  <small>*indicates required field</small>
                </v-card-text>
                <v-card-actions>
                  <v-spacer></v-spacer>
                  <v-btn color="blue darken-1" text @click="showDialog = false"
                    >Close</v-btn
                  >
                  <v-btn color="blue darken-1" text @click="showDialog = false"
                    >Submit</v-btn
                  >
                </v-card-actions>
              </v-card>
            </v-dialog>
          </v-col>
        </v-row>
      </v-container>
    </v-app-bar>
    <v-content>
      <v-container fluid>
        <router-view></router-view>
      </v-container>
    </v-content>
    <v-footer app></v-footer>
  </v-app>
</template>

<script>
export default {
  data() {
    return {
      showDrawer: true,
      showDialog: false,
      showDialog1: false,
    };
  },
};
</script>

<style lang="scss">
@import '../../assets/scss/variables.scss';
@import '../../assets/scss/common.scss';

.app-banking {
  .v-toolbar {
    &__content {
      justify-content: center;

      border-bottom: 1px solid $accentColor;
    }

    &__title {
      font-family: 'Great Vibes', cursive;
      font-size: 2.3rem !important;
      color: $accentColor;
    }
  }
}
</style>
