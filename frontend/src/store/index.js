import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    user_cards: [],
    user_transactions: [],
    user_templates: [],
    user_deposits: [],
    user_data: [],
    user_authorized: false,
    performing_request: true,
    credentials_invalid: false,
  },
  mutations: {
    ADD_CARD(state, card) {
      state.user_cards.push(card);
    },
    SET_CARDS(state, cards) {
      state.user_cards = cards;
    },
    ADD_TEMPLATE(state, template) {
      state.user_templates.push(template);
    },
    SET_TEMPLATES(state, templates) {
      state.user_templates = templates;
    },
    PERFORM_TRANSACTION(state, transaction) {
      state.user_transactions.push(transaction);
    },
    SET_TRANSACTIONS(state, transactions) {
      state.user_transactions = transactions;
    },
    CREATE_DEPOSIT(state, deposit) {
      state.user_deposits.push(deposit);
    },
    SET_DEPOSITS(state, deposits) {
      state.user_deposits = deposits;
    },
    SET_USER(state, userData) {
      state.user_data = userData;
      state.user_authorized = true;
    },
    AUTHORIZE(state) {
      state.user_authorized = true;
    },
    SET_PASSWORD(state, payload) {
      state.user_data.password = payload;
    },
    LOGOUT(state) {
      state.user_authorized = false;
    },
    ACTIVATE_REQUEST(state) {
      state.performing_request = true;
    },
    DISABLE_REQUEST(state) {
      state.performing_request = false;
    },
    INVALIDATE_CREDENTIALS(state) {
      state.credentials_invalid = true;
    },
    VALIDATE_CREDENTIALS(state) {
      state.credentials_invalid = false;
    },
  },
  actions: {
    addCard(context, payload) {
      context.commit('ADD_CARD', payload);
    },
    addTemplate(context, payload) {
      context.commit('ADD_TEMPLATE', payload);
    },
    performTransaction(context, payload) {
      context.commit('PERFORM_TRANSACTION', payload);
    },
    createDeposit(context, payload) {
      context.commit('CREATE_DEPOSIT', payload);
    },
    changePassword(context, payload) {
      context.commit('SET_PASSWORD', payload);
    },
    registerUser(context, payload) {
      context.commit('ACTIVATE_REQUEST');
      axios
        .post('/api/register', JSON.stringify(payload))
        .then(response => {
          console.log(response);
          context.commit('SET_USER', payload);
          context.commit('DISABLE_REQUEST');
        })
        .catch(error => {
          console.error(error);
          context.commit('DISABLE_REQUEST');
        });
    },
    authorizeUser(context, payload) {
      context.commit('ACTIVATE_REQUEST');
      axios
        .post('/api/authorize', JSON.stringify(payload))
        .then(response => {
          console.log(response);
          context.commit('AUTHORIZE');
          context.commit('DISABLE_REQUEST');
        })
        .catch(error => {
          console.error(error);
          context.commit('DISABLE_REQUEST');
        });
    },
    logout(context) {
      context.commit('LOGOUT');
    },
  },
  getters: {
    getCards(state) {
      return state.user_cards;
    },
    getTemplates(state) {
      return state.user_templates;
    },
    getTransactions(state) {
      return state.user_transactions;
    },
    getDeposits(state) {
      return state.user_deposits;
    },
    getUserData(state) {
      return state.user_data;
    },
    userIsAuthorized(state) {
      return state.user_authorized;
    },
    getRequestStatus(state) {
      return state.performing_request;
    },
  },
});
