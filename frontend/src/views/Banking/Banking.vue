<template>
  <v-app class="app-banking">
    <v-navigation-drawer v-model="showDrawer" app clipped v-if="userAuthorized">
      <v-list nav>
        <v-subheader>What do you want to see ?</v-subheader>
        <v-list-item-group color="primary">
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
            <v-app-bar-nav-icon
              @click.stop="showDrawer = !showDrawer"
              v-if="userAuthorized"
            >
            </v-app-bar-nav-icon>
          </v-col>
          <v-col cols="4" class="text-center">
            <v-toolbar-title>
              <router-link to="/berking/" tag="span" style="cursor: pointer">
                Berking
              </router-link>
            </v-toolbar-title>
          </v-col>
          <v-col cols="4" class="text-right">
            <v-dialog
              v-model="showDialog"
              persistent
              max-width="600px"
              v-if="!userAuthorized"
            >
              <template v-slot:activator="{ on }">
                <v-btn color="primary" dark v-on="on">Sign Up/In</v-btn>
              </template>
              <v-card>
                <v-card-title>Sign In</v-card-title>
                <v-card-text>
                  <v-container>
                    <v-row>
                      <v-col cols="12">
                        <v-form v-model="emailIsValid">
                          <v-text-field
                            label="Email*"
                            type="email"
                            required
                            :rules="emailRules"
                            v-model="user.email"
                          ></v-text-field>
                        </v-form>
                      </v-col>
                      <v-col cols="12">
                        <v-form v-model="passwordIsValid">
                          <v-text-field
                            label="Password*"
                            type="password"
                            required
                            :rules="passwordRules"
                            v-model="user.password"
                          ></v-text-field>
                        </v-form>
                      </v-col>
                      <v-col cols="12">
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
                                    <v-form v-model="firstnameIsValid">
                                      <v-text-field
                                        label="Legal first name*"
                                        required
                                        :rules="nameRules"
                                        v-model="newUser.firstName"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-form v-model="middleNameIsValid">
                                      <v-text-field
                                        label="Legal middle name*"
                                        required
                                        :rules="nameRules"
                                        v-model="newUser.middleName"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-form v-model="lastNameIsValid">
                                      <v-text-field
                                        label="Legal last name*"
                                        required
                                        :rules="nameRules"
                                        v-model="newUser.lastName"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form v-model="emailIsValid">
                                      <v-text-field
                                        label="Email*"
                                        type="email"
                                        required
                                        :rules="emailRules"
                                        v-model="newUser.email"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form v-model="passwordIsValid">
                                      <v-text-field
                                        label="Password*"
                                        type="password"
                                        required
                                        counter
                                        :rules="newPasswordRules"
                                        v-model="newUser.password"
                                      ></v-text-field>
                                    </v-form>
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
                                @click="showDialog1 = false"
                                >Close</v-btn
                              >
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="registerUser"
                                :loading="requestInProcess"
                                :disabled="
                                  !firstnameIsValid &&
                                    !middleNameIsValid &&
                                    !lastNameIsValid &&
                                    !emailIsValid &&
                                    !passwordIsValid
                                "
                                >Submit</v-btn
                              >
                            </v-card-actions>
                          </v-card>
                        </v-dialog>
                      </v-col>
                      <v-col cols="12">
                        <v-dialog
                          v-model="showDialog2"
                          persistent
                          max-width="600px"
                        >
                          <template v-slot:activator="{ on }">
                            Forgot your password ?
                            <v-btn text x-small v-on="on"
                              >Change password</v-btn
                            >
                          </template>
                          <v-card>
                            <v-card-title>
                              Change password
                            </v-card-title>
                            <v-card-text>
                              <v-container>
                                <v-row>
                                  <v-col cols="12">
                                    <v-form v-model="passwordIsValid">
                                      <v-text-field
                                        type="password"
                                        required
                                        counter
                                        label="New password"
                                        :rules="newPasswordRules"
                                        v-model="newPassword"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                </v-row>
                              </v-container>
                            </v-card-text>
                            <v-card-actions>
                              <v-spacer></v-spacer>
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="showDialog2 = false"
                                >Close</v-btn
                              >
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="changePassword"
                                :disabled="!passwordIsValid"
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
                  <v-btn
                    color="blue darken-1"
                    text
                    @click="authorizeUser"
                    :disabled="!emailIsValid || !passwordIsValid"
                    :loading="requestInProcess"
                    >Submit</v-btn
                  >
                </v-card-actions>
              </v-card>
            </v-dialog>
            <v-btn color="primary" v-else @click="logout">
              Log Out
            </v-btn>
          </v-col>
        </v-row>
      </v-container>
    </v-app-bar>
    <v-content>
      <v-container fluid v-if="userAuthorized">
        <router-view></router-view>
      </v-container>
      <v-container v-else>
        <v-row justify="center">
          <v-col cols="4">
            <v-card color="warning">
              <v-card-title class="white--text justify-center">
                Attention!
              </v-card-title>
              <v-card-text class="white--text text-center">
                To use the service authorize or register first.
                <br />
                To do, this press the button in the upper-right corner.
                <v-icon class="white--text mt-1">mdi-arrow-top-right</v-icon>
              </v-card-text>
            </v-card>
          </v-col>
        </v-row>
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
      showDialog2: false,
      emailIsValid: true,
      emailRules: [v => (v && /^.+@.+\..+$/.test(v)) || 'Invalid email'],
      passwordIsValid: true,
      passwordRules: [v => (v && v.length > 0) || 'Enter you password'],
      newPasswordRules: [
        v =>
          (v && v.length >= 10) ||
          'Password must be at least 10 characters long',
        v =>
          (v && (v.match(/\d/g) !== null && v.match(/\d/g).length >= 3)) ||
          'Password must contain at least 3 numbers',
        v =>
          (v &&
            (v.match(/[A-Z]/g) !== null && v.match(/[A-Z]/g).length >= 3)) ||
          'Password must contain at least 3 capital letters',
      ],
      firstnameIsValid: true,
      lastNameIsValid: true,
      middleNameIsValid: true,
      nameRules: [
        v => (v && v.length > 0) || 'Name cannot be empty',
        v => /^[a-zA-Z]+$/g.test(v) || 'Name can contain letters only',
      ],
      user: {
        email: '',
        password: '',
      },
      newUser: {
        firstName: '',
        middleName: '',
        lastName: '',
        email: '',
        password: '',
      },
      newPassword: '',
    };
  },
  methods: {
    authorizeUser() {
      this.$store.dispatch('authorizeUser', Object.assign({}, this.user));

      this.showDialog = this.requestInProcess;

      this.user.email = '';
      this.user.password = '';
    },
    registerUser() {
      this.$store.dispatch('registerUser', Object.assign({}, this.newUser));

      this.showDialog = this.requestInProcess;
      this.showDialog1 = this.requestInProcess;

      this.newUser.firstName = '';
      this.newUser.middleName = '';
      this.newUser.lastName = '';
      this.newUser.email = '';
      this.newUser.password = '';
    },
    changePassword() {
      this.showDialog = false;
      this.showDialog2 = false;
      this.$store.dispatch('changePassword', this.newPassword.slice(0));

      this.newPassword = '';
    },
    logout() {
      this.$store.dispatch('logout');
    },
  },
  computed: {
    userAuthorized() {
      return this.$store.getters.userIsAuthorized;
    },
    requestInProcess() {
      return this.$store.getters.getRequestStatus;
    },
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
