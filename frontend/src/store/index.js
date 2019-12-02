import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';
import createPersistedState from 'vuex-persistedstate';
import SecureLs from 'secure-ls';
import REQUEST_STATUSES from '../assets/js/vars';

const ls = new SecureLs({ isCompression: false });

Vue.use(Vuex);

export default new Vuex.Store({
  plugins: [
    createPersistedState({
      storage: {
        getItem: key => ls.get(key),
        setItem: (key, value) => ls.set(key, value),
        removeItem: key => ls.remove(key),
      },
    }),
  ],
  state: {
    request: {
      status: '',
      details: '',
      error: '',
    },
    user: {
      cards: [],
      transactions: [],
      templates: [],
      deposits: [],
      info: {},
      authorized: false,
      webtoken: '',
      refresh_token: '',
    },
  },
  mutations: {
    ADD_CARD(state, card) {
      state.user.cards.push(card);
    },
    ADD_TEMPLATE(state, template) {
      state.user.templates.push(template);
    },
    SET_CARDS(state, cards) {
      state.user.cards = cards.slice();
    },
    SET_TEMPLATES(state, templates) {
      state.user.templates = templates.slice();
    },
    SET_TRANSACTIONS(state, transactions) {
      const transact = transactions;

      transact.sort((a, b) => {
        const left = Number(
          a.date
            .match(/\d+\.\d+\.\d+/)[0]
            .split('.')
            .join('')
        );
        const right = Number(
          b.date
            .match(/\d+\.\d+\.\d+/)[0]
            .split('.')
            .join('')
        );

        if (left > right) {
          return 1;
        }
        if (left < right) {
          return -1;
        }

        return 0;
      });

      state.user.transactions = transact.slice();
    },
    SET_DEPOSITS(state, deposits) {
      state.user.deposits = deposits.slice();
    },
    SET_USER(state, userInfo) {
      state.user.info.email = userInfo.email;
      state.user.webtoken = userInfo.webtoken;
      state.user.refresh_token = userInfo.refresh_token;
      state.user.authorized = true;
    },
    UPDATE_USER_TOKENS(state, tokens) {
      state.user.webtoken = tokens.webtoken;
      state.user.refresh_token = tokens.refresh_token;
    },
    PERFORM_TRANSACTION(state, transaction) {
      state.user.transactions.push(transaction);
    },
    CREATE_DEPOSIT(state, deposit) {
      state.user.deposits.push(deposit);
    },
    LOGIN(state) {
      state.user.authorized = true;
      sessionStorage.setItem('authorized', true);
      localStorage.removeItem('vuex');
    },
    LOGOUT(state) {
      state.user.authorized = false;
      sessionStorage.setItem('authorized', false);
      localStorage.removeItem('vuex');
    },
    SET_REQUEST_STATUS(state, status) {
      state.request = status;
    },
    SET_IS_AUTHORIZED(state, status) {
      state.user.authorized = status;
      localStorage.removeItem('vuex');
    },
  },
  actions: {
    fetchDeposits(context) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Fetching deposits.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/user_deposits',
            JSON.stringify({
              email: context.getters.getUserData.email,
              webtoken: context.getters.getWebtoken,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Deposits successfuly fetched.',
            });

            const userDeposits = [];

            if (response.data.data !== 'null' && response.data.data !== null) {
              userDeposits.push(response.data.data);
            }

            context.commit('SET_DEPOSITS', userDeposits);

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to fetch deposits.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    fetchTemplates(context) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Fetching templates.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/user_templates',
            JSON.stringify({
              email: context.getters.getUserData.email,
              webtoken: context.getters.getWebtoken,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Templates successfuly fetched.',
            });

            const userTemplates = [];

            if (response.data.data !== 'null' && response.data.data !== null) {
              Object.keys(response.data.data).forEach(keyOuter => {
                if (
                  response.data.data[keyOuter] !== 'null' &&
                  response.data.data[keyOuter] !== null
                ) {
                  Object.keys(response.data.data[keyOuter]).forEach(
                    keyInner => {
                      if (
                        response.data.data[keyOuter][keyInner] !== null &&
                        response.data.data[keyOuter][keyInner] !== 'null'
                      ) {
                        userTemplates.push(
                          response.data.data[keyOuter][keyInner]
                        );
                      }
                    }
                  );
                }
              });
            }

            context.commit('SET_TEMPLATES', userTemplates);

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to fetch templates.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    fetchTransactions(context) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Fetching transactions.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/user_transactions',
            JSON.stringify({
              email: context.getters.getUserData.email,
              webtoken: context.getters.getWebtoken,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Transactions successfuly fetched.',
            });

            const userTransactions = [];

            if (response.data.data !== 'null' && response.data.data !== null) {
              Object.keys(response.data.data).forEach(keyOuter => {
                if (
                  response.data.data[keyOuter] !== 'null' &&
                  response.data.data[keyOuter] !== null
                ) {
                  Object.keys(response.data.data[keyOuter]).forEach(
                    keyInner => {
                      userTransactions.push(
                        response.data.data[keyOuter][keyInner]
                      );
                    }
                  );
                }
              });
            }

            context.commit('SET_TRANSACTIONS', userTransactions);

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to fetch transactions.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    fetchCards(context) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Fetching cards.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/user_cards',
            JSON.stringify({
              email: context.getters.getUserData.email,
              webtoken: context.getters.getWebtoken,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Cards successfuly fetched.',
            });

            const userCards = [];

            if (response.data.data !== 'null' && response.data.data !== null) {
              Object.keys(response.data.data).forEach(key => {
                userCards.push(response.data.data[key]);
              });
            }

            context.commit('SET_CARDS', userCards);

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to fetch cards.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    addCard(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Creating card for the user.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/create_card',
            JSON.stringify({
              email: context.getters.getUserData.email,
              card_name: payload,
              webtoken: context.getters.getWebtoken,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Card successfuly created.',
            });
            context.commit('ADD_CARD', response.data.data);

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to create new card.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    addTemplate(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Creating template.',
      });

      // eslint-disable-next-line no-param-reassign
      payload.webtoken = context.getters.getWebtoken;
      // eslint-disable-next-line no-param-reassign
      payload.email = context.getters.getUserData.email;

      return new Promise((resolve, reject) => {
        axios
          .post('/api/make_template', JSON.stringify(payload), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'Template created successfuly.',
              });

              context.commit('ADD_TEMPLATE', payload);
            } else {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.neg,
                details: 'Receiver card does not exist.',
              });
            }

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: 'Failed to create a template.',
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    performTransaction(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Performing transaction.',
      });

      if (payload.target_endpoint !== '/api/terminal') {
        // eslint-disable-next-line no-param-reassign
        payload.webtoken = context.getters.getWebtoken;
      }
      // eslint-disable-next-line no-param-reassign
      payload.email = context.getters.getUserData.email;

      return new Promise((resolve, reject) => {
        axios
          .post(payload.target_endpoint, JSON.stringify(payload), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'Transaction performed successfuly.',
              });

              context.commit('PERFORM_TRANSACTION', payload);
            } else {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.neg,
                details: response.data.details,
              });
            }

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: 'Failed to perform a transactiom.',
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    createDeposit(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Creating deposit.',
      });

      // eslint-disable-next-line no-param-reassign
      payload.webtoken = context.getters.getWebtoken;
      // eslint-disable-next-line no-param-reassign
      payload.email = context.getters.getUserData.email;

      console.log(payload);

      return new Promise((resolve, reject) => {
        axios
          .post('/api/make_deposit', JSON.stringify(payload), {
            headers: { 'Content-Type': 'application/json' },
          })
          .then(() => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Deposit successfuly created.',
            });

            context.commit('CREATE_DEPOSIT', payload);

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: 'Failed to create deposit.',
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    changePassword(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Changing password.',
      });

      console.log(payload);

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/recover_password',
            JSON.stringify({
              email: payload.email,
              new_password: payload.password_new,
              password: payload.password,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            console.log(response);

            if (response.data.status === 'success') {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'Password successfuly changed.',
              });
            } else {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.neg,
                details:
                  'Your old password is incorrect or you provided your old password as the new one.',
              });
            }

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: 'Failed to change password.',
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    registerUser(context, payload) {
      const newUser = {};
      newUser.user_name = payload.name_first;
      newUser.user_name += ` ${payload.name_middle}`;
      newUser.user_name += ` ${payload.name_last}`;
      newUser.user_email = payload.email;
      newUser.user_password = payload.password;

      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Registering new user.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post('/api/register', JSON.stringify(newUser), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_USER', {
                email: newUser.user_email,
                webtoken: response.data.webtoken,
                refresh_token: response.data.refresh_token,
              });

              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'New user successfuly registered.',
              });

              context.commit('LOGIN');
            } else {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.neg,
                details: 'User with such email already exists.',
              });
            }

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to register new user.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    authorizeUser(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Authorizing user.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post('/api/authorize', JSON.stringify(payload), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'User successfuly authorized.',
              });

              context.commit('LOGIN');

              context.commit('SET_USER', {
                email: payload.email,
                webtoken: response.data.webtoken,
                refresh_token: response.data.refresh_token,
              });
            } else {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.neg,
                details:
                  'You provided invalid credentials. Check your email or password',
              });
            }

            resolve(context.getters.getRequestStatus);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to authorize the user.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    logout(context) {
      context.commit('LOGOUT');
    },
    calculateIncome(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Calculating income.',
      });

      console.log(payload);

      return new Promise((resolve, reject) => {
        axios
          .post('/api/preview_before_deposit', JSON.stringify(payload), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'Deposit calculated successfuly.',
              });
            }

            resolve(response.data.data.end_sum);
          })
          .catch(error => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().failed,
              details: `Failed to calculate the deposit.`,
              error,
            });

            reject(context.getters.getRequestStatus);
          });
      });
    },
    refreshWebtoken(context) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Refreshing token.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post('/api/refresh_token', {
            refresh_token: context.getters.getRefreshToken,
            webtoken: context.getters.getWebtoken,
            email: context.getters.getUserData.email,
          })
          .then(response => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().active,
              details: 'Token successfuly refreshed.',
            });

            context.commit('UPDATE_USER_TOKENS', {
              webtoken: response.data.webtoken,
              refresh_token: response.data.refresh_token,
            });

            resolve('OK');
          })
          .catch(error => {
            reject(error);
          });
      });
    },
  },
  getters: {
    getCards(state) {
      return state.user.cards;
    },
    getTemplates(state) {
      return state.user.templates;
    },
    getTransactions(state) {
      return state.user.transactions;
    },
    getDeposits(state) {
      return state.user.deposits;
    },
    getUserData(state) {
      return state.user.info;
    },
    getAuthorizationStatus(state) {
      return state.user.authorized;
    },
    getRequestStatus(state) {
      return state.request;
    },
    getWebtoken(state) {
      return state.user.webtoken;
    },
    getRefreshToken(state) {
      return state.user.refresh_token;
    },
  },
});
