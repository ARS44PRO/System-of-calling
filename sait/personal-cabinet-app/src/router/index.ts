import { createRouter, createWebHistory } from 'vue-router';
import UserDashboard from '../views/UserDashboard.vue';

const routes = [
  {
    path: '/',
    name: 'UserDashboard',
    component: UserDashboard
  }
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
});

export default router;