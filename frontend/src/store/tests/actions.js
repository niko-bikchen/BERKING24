import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';
import REQUEST_STATUSES from '../../assets/js/vars';

Vue.use(Vuex);

const state = {
  request: {
    status: '',
    details: '',
    error: '',
  },
  user: {
    info: {},
    authorized: false,
    cards: [],
    templates: [],
  },
};

export const mutations = {
  LOGIN(state) {
    state.user.authorized = true;
  },
  SET_REQUEST_STATUS(state, status) {
    state.request = status;
  },
  SET_USER(state, userInfo) {
    state.user.info.email = userInfo.email;
    state.user.authorized = true;
  },
  SET_CARDS(state, cards) {
    state.user.cards = cards.slice(0);
  },
  SET_TEMPLATES(state, templates) {
    state.user.templates = templates.slice(0);
  },
  SET_TRANSACTIONS(state, transactions) {
    state.user.transactions = transactions.slice(0);
  },
};

export const actions = {
  authorizeUser({ commit }, payload) {
    return axios
      .post('http://localhost:34568/api/authorize', JSON.stringify(payload), {
        headers: {
          'Content-Type': 'application/json',
        },
      })
      .then(response => {
        if (response.data.status === 'success') {
          commit('SET_USER', { email: payload.email });

          commit('SET_REQUEST_STATUS', {
            status: REQUEST_STATUSES().finished.pos,
            details: 'User successfuly authorized.',
          });

          commit('LOGIN');
        } else {
          commit('SET_REQUEST_STATUS', {
            status: REQUEST_STATUSES().finished.neg,
            details: 'You provided invalid credentials.',
          });
        }
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: `Failed to register new user.`,
          error,
        });

        console.error(error);
      });
  },
  changePassword({ commit, getters }, payload) {
    if (getters.getUserData.authorized) {
      return axios
        .post(
          'http://localhost:34568/api/recover_password',
          JSON.stringify(payload),
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        )
        .then(response => {
          if (response.data.status === 'success') {
            commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.pos,
              details: 'Password successfuly changed.',
            });
          } else {
            commit('SET_REQUEST_STATUS', {
              status: REQUEST_STATUSES().finished.neg,
              details: 'You provided your old password.',
            });
          }
        })
        .catch(error => {
          commit('SET_REQUEST_STATUS', {
            status: REQUEST_STATUSES().failed,
            details: 'Failed to change password.',
            error,
          });

          console.error(error);
        });
    }

    return Promise.reject(new Error('User is not authorized.'));
  },
  registerUser({ commit }, payload) {
    const newUser = {};
    newUser.user_name = payload.name_first;
    newUser.user_name += ` ${payload.name_middle}`;
    newUser.user_name += ` ${payload.name_last}`;
    newUser.user_email = payload.email;
    newUser.user_password = payload.password;

    return axios
      .post('http://localhost:34568/api/registrate', JSON.stringify(newUser), {
        headers: {
          'Content-Type': 'application/json',
        },
      })
      .then(response => {
        if (response.data.status === 'success') {
          commit('SET_USER', {
            email: newUser.user_email,
          });

          commit('SET_REQUEST_STATUS', {
            status: REQUEST_STATUSES().finished.pos,
            details: 'New user successfuly registered.',
          });

          commit('LOGIN');
        } else {
          commit('SET_REQUEST_STATUS', {
            status: REQUEST_STATUSES().finished.neg,
            details: 'User with such email already exists.',
          });
        }
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: `Failed to register new user.`,
          error,
        });

        console.error(error);
      });
  },
  addCard({ commit }, payload) {
    return axios
      .post(
        'http://localhost:34568/api/create_card',
        JSON.stringify({
          email: payload.email,
          card_name: payload.card_name,
        }),
        {
          headers: {
            'Content-Type': 'application/json',
          },
        }
      )
      .then(() => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().finished.pos,
          details: 'Card successfuly created.',
        });
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: `Failed to create new card.`,
          error,
        });

        console.error(error);
      });
  },
  fetchCards({ commit }, payload) {
    return axios
      .post(
        'http://localhost:34568/api/user_cards',
        JSON.stringify({
          email: payload.email,
        }),
        {
          headers: {
            'Content-Type': 'application/json',
          },
        }
      )
      .then(response => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().finished.pos,
          details: 'Cards successfuly fetched.',
        });

        const userCards = [];

        if (response.data.data !== 'null' && response.data.data !== null) {
          Object.keys(response.data.data).forEach(key => {
            userCards.push(response.data.data[key]);
          });
        }

        commit('SET_CARDS', userCards);
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: `Failed to fetch cards.`,
          error,
        });

        console.error(error);
      });
  },
  addTemplate({ commit }, payload) {
    return axios
      .post(
        'http://localhost:34568/api/make_template',
        JSON.stringify(payload),
        {
          headers: {
            'Content-Type': 'application/json',
          },
        }
      )
      .then(() => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().finished.pos,
          details: 'Template created successfuly.',
        });
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: 'Failed to create a template.',
          error,
        });
      });
  },
  fetchTemplates({ commit }, payload) {
    return axios
      .post(
        'http://localhost:34568/api/user_templates',
        JSON.stringify({
          email: payload.email,
        }),
        {
          headers: {
            'Content-Type': 'application/json',
          },
        }
      )
      .then(response => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().finished.pos,
          details: 'Templates successfuly fetched.',
        });

        const userTemplates = [];

        if (response.data.data !== 'null' && response.data.data !== null) {
          console.log(response.data.data);
          Object.keys(response.data.data).forEach(keyOuter => {
            console.log(response.data.data[keyOuter]);
            if (
              response.data.data[keyOuter] !== 'null' &&
              response.data.data[keyOuter] !== null
            ) {
              Object.keys(response.data.data[keyOuter]).forEach(keyInner => {
                if (
                  response.data.data[keyOuter][keyInner] !== 'null' &&
                  response.data.data[keyOuter][keyInner] !== null
                ) {
                  userTemplates.push(response.data.data[keyOuter][keyInner]);
                }
              });
            }
          });
        }

        commit('SET_TEMPLATES', userTemplates);
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: `Failed to fetch templates.`,
          error,
        });

        console.error(error);
      });
  },
  performTransaction({ commit }, payload) {
    return axios
      .post(payload.target_endpoint, JSON.stringify(payload), {
        headers: {
          'Content-Type': 'application/json',
        },
      })
      .then(() => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().finished.pos,
          details: 'Transaction performed successfuly.',
        });
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: 'Failed to perform a transactiom.',
          error,
        });

        console.error(error);
      });
  },
  fetchTransactions({ commit }, payload) {
    axios
      .post(
        '/api/user_transactions',
        JSON.stringify({
          email: payload.email,
        }),
        {
          headers: {
            'Content-Type': 'application/json',
          },
        }
      )
      .then(response => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().finished.pos,
          details: 'Transactions successfuly fetched.',
        });

        const userTransactions = [];

        if (response.data.data !== 'null' && response.data.data !== null) {
          console.log(response.data.data);
          Object.keys(response.data.data).forEach(keyOuter => {
            console.log(response.data.data[keyOuter]);
            if (
              response.data.data[keyOuter] !== 'null' &&
              response.data.data[keyOuter] !== null
            ) {
              Object.keys(response.data.data[keyOuter]).forEach(keyInner => {
                if (
                  response.data.data[keyOuter][keyInner] !== 'null' &&
                  response.data.data[keyOuter][keyInner] !== null
                ) {
                  userTransactions.push(response.data.data[keyOuter][keyInner]);
                }
              });
            }
          });
        }

        commit('SET_TRANSACTIONS', userTransactions);
      })
      .catch(error => {
        commit('SET_REQUEST_STATUS', {
          status: REQUEST_STATUSES().failed,
          details: `Failed to fetch transactions.`,
          error,
        });

        console.error(error);
      });
  },
};

export const getters = {
  getRequestStatus(state) {
    return state.request;
  },
  getUserData(state) {
    return state.user;
  },
};

export default new Vuex.Store({
  state,
  mutations,
  actions,
  getters,
});
