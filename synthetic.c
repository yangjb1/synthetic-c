#include <synthetic.h>

void init (synthetic_state * s, tw_lp * lp) {

    tw_event *e;
    synthetic_message *m;
    std::default_random_engine rng_;

    s->internal = 0;
    s->external = 0;

    for (int i = 0; i < num_node; i++) {
        s->ts = send_distribuiton_->nextRandNum(rng_);
        e = tw_event_new(lp);
        m = tw_event_data(e);
        m->type = INTERNAL;
        tw_event_send(e);
    }
}

void event_handler (synthetic_state * s, tw_bf *bf, synthetic_message * msg, tw_lp * lp) {

    tw_event *e;
    synthetic_message *m;

    switch (msg->type) {
        case INTERNAL:
            /* schedule internal event */
            s->internal++;
            s->ts = send_distribuiton_->nextRandNum(rng);
            e = tw_event_new(lp);
            m = tw_event_data(e);
            m->type = INTERNAL;
            tw_event_send(e);

            /* schedule external event */
            e = tw_event_new(lp->rng, floating_point_ops_cnt);
            m = tw_event_data(e);
            m->type = EXTERNAL;
            tw_event_send(e);
            break;

        case EXTERNAL:
            /* process external event */
            s->external++;
            float val = 0.5;
            for (unsigned int i = 0; i < floating_point_ops_cnt; i++) {
                val += i;
            }
    }
}

void rc_event_handler (synthetic_state * s, tw_bf * bf, synthetic_message * msg, tw_lp * lp) {
    switch(msg->type) {
        case INTERNAL:
            s->internal--;
            tw_rand_reverse_unif(lp->rng);
            break;
        case EXTERNAL:
            s->external--;
            tw_rand_reverse_unif(lp->rng);
            break;
    }
}

viod final(synthetic_state * s, tw_lp * lp) {

}

tw_lptype synthetic_lps[] = {
    {
        (init_f) init,
        (pre_run_f) NULL,
        (event_f) event_handler,
        (revert_f) rc_event_handler,
        (commit_f) NULL,
        (final_f) final,
        sizeof(synthetic_state),
    },
    {0},
};

const tw_optdef app_opt[] = {
    TWOPT_GROUP("Synthetic Model"),
    TWOPT_STATE("lookahead", lookahead, "lookahead for events"),

    TWOPT_END()
};

int main (int argc, char **argv, char **env) {

    return 0;
}

