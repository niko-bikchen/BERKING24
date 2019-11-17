const axios = {
  post: jest.fn(() => Promise.resolve('Mock data')),
};
export default axios;
