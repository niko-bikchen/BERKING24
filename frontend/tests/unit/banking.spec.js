import Vue from 'vue';
import Vuex from 'vuex';
import { actions, mutations, getters } from '../../src/store/tests/actions';
import REQUEST_STATUSES from '../../src/assets/js/vars';

Vue.use(Vuex);

describe('authorization', () => {
  let store;
  beforeEach(() => {
    store = new Vuex.Store({
      state: {
        user: {
          info: {},
          authorized: false,
        },
        request: {
          status: '',
          details: '',
          error: '',
        },
      },
      mutations,
      actions: {
        authorizeUser: actions.authorizeUser,
        changePassword: actions.changePassword,
      },
      getters,
    });
  });

  it('cannot authorize user with invalid credentials', () => {
    return store
      .dispatch('authorizeUser', {
        email: 'john.doe@gmail.com',
        password: '12345',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.neg
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'You provided invalid credentials.'
        );
      });
  });

  it('can authorize user with valid credentials', () => {
    return store
      .dispatch('authorizeUser', {
        email: 'jane.doe@gmail.com',
        password: '12345',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'User successfuly authorized.'
        );
      });
  });

  it('can change password of an authorized user', () => {
    store.state.user.authorized = true;

    return store
      .dispatch('changePassword', {
        email: 'jane.doe@gmail.com',
        new_password: '56789',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Password successfuly changed.'
        );
      });
  });

  it('can authorize user with the new password', () => {
    return store
      .dispatch('authorizeUser', {
        email: 'jane.doe@gmail.com',
        password: '56789',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'User successfuly authorized.'
        );
      });
  });

  it('cannot change password of an unauthorized user', () => {
    store.state.user.authorized = false;

    return store
      .dispatch('changePassword', {
        email: 'jane.doe@gmail.com',
        new_password: '12345',
      })
      .then(
        () => {
          expect(store.getters.getRequestStatus.status).toEqual(
            REQUEST_STATUSES().finished.pos
          );

          expect(store.getters.getRequestStatus.details).toEqual(
            'Password successfuly changed.'
          );
        },
        reason => {
          expect(reason.message).toEqual('User is not authorized.');
        }
      );
  });
});

describe('registaration', () => {
  let store;
  beforeEach(() => {
    store = new Vuex.Store({
      state: {
        user: {
          info: {},
          authorized: false,
        },
        request: {
          status: '',
          details: '',
          error: '',
        },
      },
      mutations,
      actions: {
        registerUser: actions.registerUser,
      },
      getters,
    });
  });

  it('registers new users', () => {
    return store
      .dispatch('registerUser', {
        name_first: 'John',
        name_middle: 'David',
        name_last: 'Doe',
        email: 'john.doe@gmail.com',
        password: '12345',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'New user successfuly registered.'
        );
      });
  });

  it('cannot register the user with the same email', () => {
    return store
      .dispatch('registerUser', {
        name_first: 'Jane',
        name_middle: 'David',
        name_last: 'Doe',
        email: 'jane.doe@gmail.com',
        password: '12345',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.neg
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'User with such email already exists.'
        );
      });
  });
});

describe('card creation', () => {
  let store;
  beforeEach(() => {
    store = new Vuex.Store({
      state: {
        user: {
          info: {},
          authorized: false,
          cards: [],
        },
        request: {
          status: '',
          details: '',
          error: '',
        },
      },
      mutations,
      actions: {
        addCard: actions.addCard,
        fetchCards: actions.fetchCards,
      },
      getters,
    });
  });

  it('creates a card for the user', () => {
    return store
      .dispatch('addCard', {
        email: 'jane.doe@gmail.com',
        card_name: 'Test Card',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Card successfuly created.'
        );
      });
  });

  it('fetches user cards from the server', () => {
    return store
      .dispatch('fetchCards', {
        email: 'jane.doe@gmail.com',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Cards successfuly fetched.'
        );

        const newCard = {};
        const { cards } = store.getters.getUserData;

        for (let i = 0; i < cards.length; i += 1) {
          if (cards[i].card_name === 'Test Card') {
            Object.assign(newCard, cards[i]);
          }
        }

        expect(newCard.card_name).toEqual('Test Card');
      });
  });
});

describe('template creation', () => {
  let store;
  beforeEach(() => {
    store = new Vuex.Store({
      state: {
        user: {
          info: {},
          authorized: false,
          templates: [],
        },
        request: {
          status: '',
          details: '',
          error: '',
        },
      },
      mutations,
      actions: {
        addTemplate: actions.addTemplate,
        fetchTemplates: actions.fetchTemplates,
      },
      getters,
    });
  });

  it('creates a template for the user', () => {
    return store
      .dispatch('addTemplate', {
        sender_card: '5679777493006716',
        receiver_card: '5679476667017630',
        sum: '200',
        description: 'Test template',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Template created successfuly.'
        );
      });
  });

  it('fetches user templates from the server', () => {
    return store
      .dispatch('fetchTemplates', {
        email: 'jane.doe@gmail.com',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Templates successfuly fetched.'
        );

        expect(store.getters.getUserData.templates[0].sender_card).toEqual(
          '5679777493006716'
        );
      });
  });
});

describe('making transactions', () => {
  const store = new Vuex.Store({
    state: {
      user: {
        info: {},
        transactions: [],
        cards: [],
      },
      request: {
        status: '',
        details: '',
        error: '',
      },
    },
    mutations,
    actions: {
      performTransaction: actions.performTransaction,
      fetchTransactions: actions.fetchTransactions,
      fetchCards: actions.fetchCards,
    },
    getters,
  });

  it('makes a transaction', () => {
    return store
      .dispatch('performTransaction', {
        sender_card: '5679777493006716',
        receiver_card: '5679476667017630',
        sum: '200',
        description: 'Test transaction',
        target_endpoint: 'http://localhost:34568/api/make_transaction',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Transaction performed successfuly.'
        );
      });
  });

  it('makes a transaction correctly', () => {
    return store
      .dispatch('fetchCards', {
        email: 'jane.doe@gmail.com',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Cards successfuly fetched.'
        );

        const { cards } = store.getters.getUserData;

        for (let i = 0; i < cards.length; i += 1) {
          if (cards[i].card_number === '5679777493006716') {
            expect(parseFloat(cards[i].card_balance)).toBe(300.0);
          }
          if (cards[i].card_number === '5679476667017630') {
            expect(parseFloat(cards[i].card_balance)).toBe(200.0);
          }
        }
      });
  });

  it('fetches the transactions from the server', () => {
    return store
      .dispatch('fetchTransactions', {
        email: 'jane.doe@gmail.com',
      })
      .then(() => {
        expect(store.getters.getRequestStatus.status).toEqual(
          REQUEST_STATUSES().finished.pos
        );

        expect(store.getters.getRequestStatus.details).toEqual(
          'Transactions successfuly fetched.'
        );

        expect(store.getters.getUserData.transactions[0].sender_card).toEqual(
          '5679777493006716'
        );
      });
  });
});
