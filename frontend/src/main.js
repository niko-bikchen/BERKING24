import axios from 'axios';
import Vue from 'vue';
import App from './App.vue';
import router from './router';
import store from './store';
import vuetify from './plugins/vuetify';

Vue.config.productionTip = false;

axios.defaults.baseURL =
  'https://69a1d4bb-4dce-43ca-9887-04c63f4440e7.mock.pstmn.io/';

Vue.directive('test', {
  bind(el, binding) {
    Object.keys(binding.value).forEach(value => {
      el.setAttribute(`data-test-${value}`, binding.value[value]);
    });
  },
});

Vue.filter('formatCardNum', cardNum => {
  let num = cardNum;

  if (Number.isInteger(num)) {
    num = cardNum.toString();
  }

  let formattedCardNum = '';

  for (let i = 4; i <= 16; i += 4) {
    formattedCardNum += `${num.slice(i - 4, i)} \u2014 `;
  }

  return formattedCardNum.slice(0, formattedCardNum.length - 2);
});

Vue.filter('formatCardNumWithMask', cardNum => {
  let num = cardNum;

  if (Number.isInteger(num)) {
    num = cardNum.toString();
  }

  return `${num.slice(0, 4)} \u2014 .... \u2014 .... \u2014 ${num.slice(
    12,
    16
  )}`;
});

new Vue({
  router,
  store,
  vuetify,
  render: h => h(App),
}).$mount('#app');
