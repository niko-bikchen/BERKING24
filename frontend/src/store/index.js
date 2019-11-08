import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    user_cards: [],
    user_transactions: [],
    user_templates: [],
    user_deposits: [],
    user_data: [],
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
    },
  },
  actions: {
    addCard(context, payload) {
      // TODO: perform POST request to the server

      context.commit('ADD_CARD', payload);
    },
    addTemplate(context, payload) {
      // TODO: perform POST request to the server

      context.commit('ADD_TEMPLATE', payload);
    },
    performTransaction(context, payload) {
      // TODO: perform POST request to the server

      context.commit('PERFORM_TRANSACTION', payload);
    },
    createDeposit(context, payload) {
      // TODO: perform POST request to the server

      context.commit('CREATE_DEPOSIT', payload);
    },
    fetchUserCards() {
      // TODO: perform GET request to the server
    },
    fetchUserTransactions() {
      // TODO: perform GET request to the server
    },
    fetchUserTemplates() {
      // TODO: perform GET request to the server
    },
    fetchUserDeposits() {
      // TODO: perform GET request to the server
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
  },
});
