/* procedure CalculateKey(s) */
/* return [min(g(s),rhs(s)) + h(s_start,s)+k_m;min(g(s),rhs(s))]; */


/* procedure Initialize() */
/* U = \nullset;
 * k_m = 0;
 * for all s \elemof rhs(s) = g(s) = \inf;
 * rhs(s_goal) = 0;
 * U.insert(s_goal,[h(s_start,s_goal);0]);
 */

/* procedure UpdateVertex(u) */
/* if (g(u) != rhs(u) AND u \elemof U)          U.update(u, CalculateKey(u));
 * else if (g(u) != rhs(u) AND u \not_elemof U) U.Insert(u,CalculateKey(u));
 * else if (g(u) =  rhs(u) AND u \elemof U)     U.Remove(u);
 */

/* procedure ComputeShortestPath() */
/* while (U.TopKey() < CalculateKey(s_start) OR rhs(s_start) > g(s_start))
 *   u = U.Top();
 *   k_old = U.TopKey()
 *   k_new = CalculateKey(u));
 *   if (k_old < k_new)
 *     U.Update(u, k_new);
 *   else if (g(u) > rhs(u))
 *     g(u) = rhs(u);
 *     U.Remove(u);
 *     for all s \elemof Pred(u)
 *       if (s != s_goal) rhs(s) = min(rhs(s), c(s,u) + g(u));
 *       UpdateVertex(s);
 *   else
 *    g_old = g(u);
 *    g(u) = inf;
 *    for all s \elemof Pred(u) \union {u}
 *      if (rhs(s) = c(s,u) + g_old)
 *        if (s != s_goal) rhs(s) = min_{s' \elemof Succ(s)}(c(s,s') + g(s'));
 *      UpdateVertex(s);
 */

/* procedure Main() */
/* s_last = s_start
 * Initialize();
 * ComputeShortestPath();
 * while(s_start != s_goal)
 *   ## If (rhs(s_start) = inf) then there is no known path ##
 *   s_start = arg min_{s' \elemof Succ(s_start)(c(s_start, s') + g(s'));
 *   Move to s_start;
 *   Scan graph for changed edge costs;
 *   if any edge costs changed
 *     k_m = k_m = h(s_last, s_start);
 *     s_last = s_start;
 *     for all directed edges(u,v) with changed edge costs
 *       c_old = c(u,v);
 *       Update the edge cost c(u,v);
 *       if (c_old > c(u,v))
 *         if (u != s_goal) rhs(u) = min(rhs(u), c(u,v) + g(v));
 *       else if (rhs(u) = c_old + g(v))
 *         if (u != s_goal) rhs(u) = min_{s' \elemof Succ(u)}(c(u,s') + g(s'));
 *       UpdateVertex(u);
 *     ComputeShortestPath();
 */
