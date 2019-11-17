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
          <v-list-item exact to="/">
            <v-list-item-content>
              <v-list-item-title>Root</v-list-item-title>
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
              <router-link to="/berking/" tag="span" class="header-title">
                Berking
              </router-link>
              <v-chip color="primary" small>
                beta
              </v-chip>
            </v-toolbar-title>
          </v-col>
          <v-col cols="4" class="text-right">
            <v-dialog
              v-model="dialogs.showAuthDialog"
              persistent
              max-width="600px"
              v-if="!userAuthorized"
            >
              <template v-slot:activator="{ on }">
                <span class="kek"> </span>
                <v-btn color="primary" dark v-on="on" v-test="{ id: 'sgn-btn' }"
                  >Sign Up/In</v-btn
                >
              </template>
              <v-card>
                <v-card-title>Sign In</v-card-title>
                <v-card-text>
                  <v-container>
                    <v-row>
                      <v-col cols="12">
                        <v-form v-model="credValid.email.isValid">
                          <v-text-field
                            label="Email*"
                            type="email"
                            required
                            :rules="credValid.email.rules"
                            v-model="user.email"
                          ></v-text-field>
                        </v-form>
                      </v-col>
                      <v-col cols="12">
                        <v-form v-model="credValid.password.isValid">
                          <v-text-field
                            label="Password*"
                            type="password"
                            required
                            :rules="credValid.password.ifExistsRules"
                            v-model="user.password"
                          ></v-text-field>
                        </v-form>
                      </v-col>
                      <v-col cols="12">
                        <v-dialog
                          v-model="dialogs.showRegistDialog"
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
                                    <v-form
                                      v-model="credValid.user_name.firstIsValid"
                                    >
                                      <v-text-field
                                        label="Legal first name*"
                                        required
                                        :rules="credValid.user_name.rules"
                                        v-model="new_user.name_first"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-form
                                      v-model="
                                        credValid.user_name.middleIsValid
                                      "
                                    >
                                      <v-text-field
                                        label="Legal middle name*"
                                        required
                                        :rules="credValid.user_name.rules"
                                        v-model="new_user.name_middle"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12" sm="6" md="4">
                                    <v-form
                                      v-model="credValid.user_name.lastIsValid"
                                    >
                                      <v-text-field
                                        label="Legal last name*"
                                        required
                                        :rules="credValid.user_name.rules"
                                        v-model="new_user.name_last"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form v-model="credValid.email.isValid">
                                      <v-text-field
                                        label="Email*"
                                        type="email"
                                        required
                                        :rules="credValid.email.rules"
                                        v-model="new_user.email"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form
                                      v-model="credValid.password.isValid"
                                    >
                                      <v-text-field
                                        label="Password*"
                                        type="password"
                                        required
                                        counter
                                        :rules="credValid.password.ifNewRules"
                                        v-model="new_user.password"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-scroll-x-transition>
                                    <v-col
                                      cols="12"
                                      v-if="processes.registr.bad"
                                    >
                                      <v-alert dense outlined type="error">
                                        {{ processes.registr.details }}
                                      </v-alert>
                                    </v-col>
                                  </v-scroll-x-transition>
                                  <v-scroll-x-transition>
                                    <v-col
                                      cols="12"
                                      v-if="processes.registr.failed"
                                    >
                                      <v-alert dense outlined type="error">
                                        {{ processes.registr.details }}
                                      </v-alert>
                                    </v-col>
                                  </v-scroll-x-transition>
                                </v-row>
                              </v-container>
                            </v-card-text>
                            <v-card-actions>
                              <v-spacer></v-spacer>
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="dialogs.showRegistDialog = false"
                                >Close</v-btn
                              >
                              <v-btn
                                color="blue darken-1"
                                text
                                @click="registerUser"
                                :loading="processes.registr.active"
                                :disabled="newUserDataValid"
                                >Submit</v-btn
                              >
                            </v-card-actions>
                          </v-card>
                        </v-dialog>
                      </v-col>
                      <v-col cols="12">
                        <v-dialog
                          persistent
                          max-width="600px"
                          v-model="dialogs.showPassRenovDialog"
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
                                    <v-form
                                      v-model="credValid.password.isValid"
                                    >
                                      <v-text-field
                                        type="password"
                                        required
                                        counter
                                        label="New password"
                                        :rules="credValid.password.ifNewRules"
                                        v-model="user.password_new"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-scroll-x-transition>
                                    <v-col
                                      cols="12"
                                      v-if="processes.change_password.bad"
                                    >
                                      <v-alert dense outlined type="error">
                                        {{ processes.change_password.details }}
                                      </v-alert>
                                    </v-col>
                                  </v-scroll-x-transition>
                                  <v-scroll-x-transition>
                                    <v-col
                                      cols="12"
                                      v-if="processes.change_password.failed"
                                    >
                                      <v-alert dense outlined type="error">
                                        {{ processes.change_password.details }}
                                      </v-alert>
                                    </v-col>
                                  </v-scroll-x-transition>
                                </v-row>
                              </v-container>
                            </v-card-text>
                            <v-card-actions>
                              <v-spacer></v-spacer>
                              <v-btn color="blue darken-1" text>Close</v-btn>
                              <v-btn
                                color="blue darken-1"
                                text
                                :loading="processes.change_password.active"
                                @click="changePassword"
                                :disabled="false"
                                >Submit</v-btn
                              >
                            </v-card-actions>
                          </v-card>
                        </v-dialog>
                      </v-col>
                      <v-scroll-x-transition>
                        <v-col cols="12" v-if="processes.auth.bad">
                          <v-alert dense outlined type="error">
                            {{ processes.auth.details }}
                          </v-alert>
                        </v-col>
                      </v-scroll-x-transition>
                      <v-scroll-x-transition>
                        <v-col cols="12" v-if="processes.auth.failed">
                          <v-alert dense outlined type="error">
                            {{ processes.auth.details }}
                          </v-alert>
                        </v-col>
                      </v-scroll-x-transition>
                    </v-row>
                  </v-container>
                </v-card-text>
                <v-card-actions>
                  <v-spacer></v-spacer>
                  <v-btn
                    color="blue darken-1"
                    text
                    @click="dialogs.showAuthDialog = false"
                    >Close</v-btn
                  >
                  <v-btn
                    color="blue darken-1"
                    text
                    @click="authorizeUser"
                    :disabled="
                      !credValid.email.isValid || !credValid.password.isValid
                    "
                    :loading="processes.auth.active"
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
import REQUEST_STATUSES from '../../assets/js/vars';

export default {
  data() {
    return {
      showDrawer: true,
      dialogs: {
        showAuthDialog: false,
        showRegistDialog: false,
        showPassRenovDialog: false,
      },
      credValid: {
        email: {
          isValid: true,
          rules: [v => (v && /^.+@.+\..+$/.test(v)) || 'Invalid email'],
        },
        password: {
          isValid: true,
          ifExistsRules: [v => (v && v.length > 0) || 'Enter you password'],
          ifNewRules: [
            v =>
              (v && v.length >= 10) ||
              'Password must be at least 10 characters long',
            v =>
              (v && v.match(/\d/g) !== null && v.match(/\d/g).length >= 3) ||
              'Password must contain at least 3 numbers',
            v =>
              (v &&
                v.match(/[A-Z]/g) !== null &&
                v.match(/[A-Z]/g).length >= 3) ||
              'Password must contain at least 3 capital letters',
          ],
        },
        user_name: {
          firstIsValid: true,
          lastIsValid: true,
          middleIsValid: true,
          rules: [
            v => (v && v.length > 0) || 'Name cannot be empty',
            v => /^[a-zA-Z]+$/g.test(v) || 'Name can contain letters only',
          ],
        },
      },
      user: {
        email: '',
        password: '',
        password_new: '',
      },
      new_user: {
        name_first: '',
        name_middle: '',
        name_last: '',
        email: '',
        password: '',
      },
      processes: {
        auth: {
          active: false,
          bad: false,
          failed: false,
          details: '',
          error: '',
        },
        registr: {
          active: false,
          bad: false,
          failed: false,
          details: '',
          error: '',
        },
        change_password: {
          active: false,
          bad: false,
          failed: false,
          details: '',
          error: '',
        },
      },
    };
  },
  beforeMount() {
    if (sessionStorage.getItem('authorized') === true) {
      this.$store.dispatch('restoreAuth', true);
    }
  },
  methods: {
    authorizeUser() {
      this.processes.auth.active = true;

      this.$store.dispatch('authorizeUser', Object.assign({}, this.user)).then(
        requestStatus => {
          if (requestStatus.status === REQUEST_STATUSES().finished.pos) {
            this.showAuthDialog = false;
            this.showRegistDialog = false;

            this.processes.auth.active = false;
            this.processes.auth.bad = false;
            this.processes.auth.failed = false;

            this.user.email = '';
            this.user.password = '';

            localStorage.removeItem('vuex');

            if (this.$route.path !== '/berking') {
              this.$router.push({ path: '/berking' });
            }
          }
          if (requestStatus.status === REQUEST_STATUSES().finished.neg) {
            this.processes.auth.active = false;
            this.processes.auth.failed = false;
            this.processes.auth.bad = true;
            this.processes.auth.details = requestStatus.details;
          }
        },
        requestStatus => {
          this.processes.auth.bad = false;
          this.processes.auth.active = false;
          this.processes.auth.failed = true;
          this.processes.auth.details = requestStatus.details;
          this.processes.auth.error = requestStatus.error;
        }
      );
    },
    registerUser() {
      this.processes.registr.active = true;

      this.$store
        .dispatch('registerUser', Object.assign({}, this.new_user))
        .then(
          requestStatus => {
            if (requestStatus.status === REQUEST_STATUSES().finished.pos) {
              this.showRegistDialog = false;
              this.showAuthDialog = false;

              this.processes.registr.active = false;
              this.processes.registr.bad = false;
              this.processes.registr.failed = false;

              this.new_user.name_first = '';
              this.new_user.name_middle = '';
              this.new_user.name_last = '';
              this.new_user.email = '';
              this.new_user.password = '';

              localStorage.removeItem('vuex');

              if (this.$route.path !== '/berking') {
                this.$router.push({ path: '/berking' });
              }
            }
            if (requestStatus.status === REQUEST_STATUSES().finished.neg) {
              this.processes.registr.active = false;
              this.processes.registr.failed = false;
              this.processes.registr.bad = true;
              this.processes.registr.details = requestStatus.details;
            }
          },
          requestStatus => {
            this.processes.registr.bad = false;
            this.processes.registr.active = false;
            this.processes.registr.failed = true;
            this.processes.registr.details = requestStatus.details;
            this.processes.registr.error = requestStatus.error;
          }
        );
    },
    changePassword() {
      this.processes.change_password.active = true;
      this.$store
        .dispatch('changePassword', this.user.password_new.slice(0))
        .then(
          requestStatus => {
            if (requestStatus.status === REQUEST_STATUSES().finished.pos) {
              this.dialogs.showPassRenovDialog = false;

              this.processes.change_password.active = false;
              this.processes.change_password.bad = false;
              this.processes.change_password.failed = false;

              this.user.password_new = '';
            }
            if (requestStatus.status === REQUEST_STATUSES().finished.neg) {
              this.processes.change_password.active = false;
              this.processes.change_password.failed = false;
              this.processes.change_password.bad = true;
              this.processes.change_password.details = requestStatus.details;
            }
          },
          requestStatus => {
            this.processes.change_password.bad = false;
            this.processes.change_password.active = false;
            this.processes.change_password.failed = true;
            this.processes.change_password.details = requestStatus.details;
            this.processes.change_password.error = requestStatus.error;
          }
        );
    },
    logout() {
      this.$store.dispatch('logout');
    },
  },
  computed: {
    userAuthorized() {
      return this.$store.getters.getAuthorizationStatus;
    },
    requestStatus() {
      return this.$store.getters.getRequestStatus;
    },
    newUserDataValid() {
      return (
        !this.credValid.email.isValid ||
        !this.credValid.password.isValid ||
        !this.credValid.user_name.firstIsValid ||
        !this.credValid.user_name.middleIsValid ||
        !this.credValid.user_name.lastIsValid
      );
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

    .header-title {
      font-family: 'Great Vibes', cursive;
      font-size: 2.3rem !important;
      color: $accentColor;
      cursor: pointer;
    }
  }
}
</style>
