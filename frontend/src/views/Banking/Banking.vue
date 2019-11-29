<template>
  <v-app class="app-banking">
    <v-navigation-drawer v-model="showDrawer" app clipped v-if="userAuthorized">
      <v-list nav>
        <v-subheader>What do you want to see ?</v-subheader>
        <v-list-item-group color="primary">
          <v-list-item exact to="/berking">
            <v-list-item-icon><v-icon>mdi-home</v-icon></v-list-item-icon>
            <v-list-item-content>
              <v-list-item-title>Home</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/cards">
            <v-list-item-icon
              ><v-icon
                >mdi-credit-card-multiple-outline</v-icon
              ></v-list-item-icon
            >
            <v-list-item-content>
              <v-list-item-title>Cards</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/transactions">
            <v-list-item-icon
              ><v-icon
                >mdi-format-list-bulleted-square</v-icon
              ></v-list-item-icon
            >
            <v-list-item-content>
              <v-list-item-title>Transactions</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/templates">
            <v-list-item-icon
              ><v-icon>mdi-file-document-edit-outline</v-icon></v-list-item-icon
            >
            <v-list-item-content>
              <v-list-item-title>Templates</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/berking/deposits">
            <v-list-item-icon
              ><v-icon>mdi-cash-multiple</v-icon></v-list-item-icon
            >
            <v-list-item-content>
              <v-list-item-title>Deposit</v-list-item-title>
            </v-list-item-content>
          </v-list-item>
          <v-list-item exact to="/">
            <v-list-item-icon
              ><v-icon>mdi-source-commit-start</v-icon></v-list-item-icon
            >
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
                            label="Email"
                            type="email"
                            outlined
                            required
                            :rules="credValid.email.rules"
                            v-model="user.email"
                          ></v-text-field>
                        </v-form>
                      </v-col>
                      <v-col cols="12">
                        <v-form v-model="credValid.password.isValid">
                          <v-text-field
                            label="Password"
                            type="password"
                            outlined
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
                                        label="Legal first name"
                                        required
                                        outlined
                                        :success="
                                          credValid.user_name.firstIsValid
                                        "
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
                                        label="Legal middle name"
                                        required
                                        outlined
                                        :success="
                                          credValid.user_name.middleIsValid
                                        "
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
                                        label="Legal last name"
                                        required
                                        outlined
                                        :success="
                                          credValid.user_name.lastIsValid
                                        "
                                        :rules="credValid.user_name.rules"
                                        v-model="new_user.name_last"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form v-model="credValid.email.isValid">
                                      <v-text-field
                                        label="Email"
                                        type="email"
                                        required
                                        outlined
                                        :success="credValid.email.isValid"
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
                                        label="Password"
                                        type="password"
                                        required
                                        outlined
                                        :error="!passwordIsValid"
                                        :success="passwordIsValid"
                                        v-model="new_user.password"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-checkbox
                                      v-model="passwordLength"
                                      :success="passwordLength"
                                      :error="!passwordLength"
                                      label="Password must be at least 10 characters long"
                                      readonly
                                    ></v-checkbox>
                                    <v-checkbox
                                      v-model="passwordNumbers"
                                      :success="passwordNumbers"
                                      :error="!passwordNumbers"
                                      label="Password must contain at least 3 numbers"
                                      readonly
                                    ></v-checkbox>
                                    <v-checkbox
                                      v-model="passwordLetters"
                                      :success="passwordLetters"
                                      :error="!passwordLetters"
                                      label="Password must be at least 3 capital letters"
                                      readonly
                                    ></v-checkbox>
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
                                color="primary"
                                outlined
                                @click="dialogs.showRegistDialog = false"
                                >Close</v-btn
                              >
                              <v-btn
                                color="primary"
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
                                    <v-form v-model="credValid.email.isValid">
                                      <v-text-field
                                        type="email"
                                        required
                                        outlined
                                        label="Email"
                                        :rules="credValid.email.rules"
                                        v-model="new_password.email"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form
                                      v-model="credValid.password.isValid"
                                    >
                                      <v-text-field
                                        type="password"
                                        required
                                        outlined
                                        label="Old password"
                                        :rules="
                                          credValid.password.ifExistsRules
                                        "
                                        v-model="new_password.password"
                                      ></v-text-field>
                                    </v-form>
                                  </v-col>
                                  <v-col cols="12">
                                    <v-form
                                      v-model="credValid.password.isValid"
                                    >
                                      <v-text-field
                                        type="password"
                                        required
                                        outlined
                                        label="New password"
                                        :rules="credValid.password.ifNewRules"
                                        v-model="new_password.password_new"
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
                                  <v-scroll-x-transition>
                                    <v-col
                                      cols="12"
                                      v-if="processes.change_password.good"
                                    >
                                      <v-alert dense outlined type="success">
                                        {{ processes.change_password.details }}
                                      </v-alert>
                                    </v-col>
                                  </v-scroll-x-transition>
                                </v-row>
                              </v-container>
                            </v-card-text>
                            <v-card-actions>
                              <v-spacer></v-spacer>
                              <v-btn
                                color="primary"
                                @click="dialogs.showPassRenovDialog = false"
                                :disabled="processes.change_password.good"
                                outlined
                                >Close</v-btn
                              >
                              <v-btn
                                color="primary"
                                :loading="processes.change_password.active"
                                @click="changePassword"
                                :disabled="processes.change_password.good"
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
                    color="primary"
                    outlined
                    @click="dialogs.showAuthDialog = false"
                    >Close</v-btn
                  >
                  <v-btn
                    color="primary"
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
        <v-fade-transition mode="out-in">
          <router-view></router-view>
        </v-fade-transition>
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
      },
      new_user: {
        name_first: '',
        name_middle: '',
        name_last: '',
        email: '',
        password: '',
      },
      new_password: {
        email: '',
        password: '',
        new_password: '',
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
          good: false,
          failed: false,
          details: '',
          error: '',
        },
      },
    };
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
        .dispatch('changePassword', Object.assign({}, this.new_password))
        .then(
          requestStatus => {
            if (requestStatus.status === REQUEST_STATUSES().finished.pos) {
              this.processes.change_password.active = false;
              this.processes.change_password.bad = false;
              this.processes.change_password.failed = false;
              this.processes.change_password.good = true;

              this.user.password_new = '';
              this.user.password = '';
              this.user.email = '';

              setTimeout(() => {
                this.dialogs.showPassRenovDialog = false;
                this.processes.change_password.good = false;
              }, 1000);
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
        !this.passwordIsValid ||
        !this.credValid.user_name.firstIsValid ||
        !this.credValid.user_name.middleIsValid ||
        !this.credValid.user_name.lastIsValid
      );
    },
    passwordLength() {
      return (
        this.credValid.password.ifNewRules[0](this.new_user.password) === true
      );
    },
    passwordNumbers() {
      return (
        this.credValid.password.ifNewRules[1](this.new_user.password) === true
      );
    },
    passwordLetters() {
      return (
        this.credValid.password.ifNewRules[2](this.new_user.password) === true
      );
    },
    passwordIsValid() {
      return (
        this.passwordLength && this.passwordNumbers && this.passwordLetters
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
