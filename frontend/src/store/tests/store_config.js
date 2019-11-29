import axios from 'axios';
import REQUEST_STATUSES from '../../assets/js/vars';

export default {
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
      state.user.cards = [...cards];
    },
    SET_TEMPLATES(state, templates) {
      state.user.templates = [...templates];
    },
    SET_TRANSACTIONS(state, transactions) {
      state.user.transactions = [...transactions];
    },
    SET_DEPOSITS(state, deposits) {
      state.user.deposits = [...deposits];
    },
    SET_USER(state, userInfo) {
      state.user.info.email = userInfo.email;
      state.user.authorized = true;
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
    },
    LOGOUT(state) {
      state.user.authorized = false;
      sessionStorage.setItem('authorized', false);
    },
    SET_REQUEST_STATUS(state, status) {
      state.request = status;
    },
    SET_IS_AUTHORIZED(state, status) {
      state.user.authorized = status;
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
            '/api/user_templates',
            JSON.stringify({
              email: context.getters.getUserData.email,
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

            if (response.data.data !== 'null') {
              Object.keys(response.data.data).forEach(keyOuter => {
                Object.keys(response.data.data[keyOuter]).forEach(keyInner => {
                  userDeposits.push(response.data.data[keyOuter][keyInner]);
                });
              });
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
                      userTemplates.push(
                        response.data.data[keyOuter][keyInner]
                      );
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
    restoreAuth(context, status) {
      context.commit('SET_IS_AUTHORIZED', status);
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

      return new Promise((resolve, reject) => {
        axios
          .post('/api/make_template', JSON.stringify(payload), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(() => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Template created successfuly.',
            });

            context.commit('ADD_TEMPLATE', payload);

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

      return new Promise((resolve, reject) => {
        axios
          .post(payload.target_endpoint, JSON.stringify(payload), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(() => {
            context.commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Transaction performed successfuly.',
            });

            context.commit('PERFORM_TRANSACTION', payload);

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
      context.commit('CREATE_DEPOSIT', payload);
    },
    changePassword(context, payload) {
      context.commit('SET_REQUEST_STATUS', {
        status: REQUEST_STATUSES().active,
        details: 'Changing password.',
      });

      return new Promise((resolve, reject) => {
        axios
          .post(
            '/api/recover_password',
            JSON.stringify({
              email: context.getters.getUserData.email,
              new_password: payload,
            }),
            {
              headers: {
                'Content-Type': 'application/json',
              },
            }
          )
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.pos,
                details: 'Password successfuly changed.',
              });
            } else {
              context.commit('SET_REQUEST_STATUS', {
                status: REQUEST_STATUSES().finished.neg,
                details: 'You provided your old password.',
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
          .post('/api/registrate', JSON.stringify(newUser), {
            headers: {
              'Content-Type': 'application/json',
            },
          })
          .then(response => {
            if (response.data.status === 'success') {
              context.commit('SET_USER', {
                email: newUser.user_email,
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

              context.commit('SET_USER', { email: payload.email });
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
  },
};
