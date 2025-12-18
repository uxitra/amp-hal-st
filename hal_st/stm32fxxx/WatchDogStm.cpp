#include "hal_st/stm32fxxx/WatchDogStm.hpp"

namespace hal
{
    WatchDogStm::WatchDogStm(const infra::Function<void()>& onExpired, const Config& config)
        : maxMissedFeeds(config.maxMissedFeeds)
        , onExpired(onExpired)
        , interruptRegistration(WWDG_IRQn, [this]()
              {
                  Interrupt();
              })
    {
        __WWDG_CLK_ENABLE();
#if defined(STM32H7)
        handle.Instance = WWDG1;
#else
        handle.Instance = WWDG;
#endif
        handle.Init.Prescaler = config.prescaler;
        handle.Init.Window = WWDG_CR_T;
        handle.Init.Counter = WWDG_CR_T;
#ifdef STM32F7
        handle.Init.EWIMode = WWDG_EWI_ENABLE;
#endif
        HAL_WWDG_Init(&handle);

        SCB->AIRCR = (0x5FAUL << SCB_AIRCR_VECTKEY_Pos)
#ifndef STM32G0
                     | (0 << SCB_AIRCR_PRIGROUP_Pos)
#endif
            ;
        NVIC_SetPriority(WWDG_IRQn, 0);
#if defined(STM32H7)
        WWDG1->CFR |= WWDG_CFR_EWI;
#else
        WWDG->CFR |= WWDG_CFR_EWI;
#endif

        feedingTimer.Start(config.feedTimerInterval, [this]()
            {
                Feed();
            });
    }

    void WatchDogStm::WatchDogRefresh()
    {
        HAL_WWDG_Refresh(&handle);
#if defined(STM32H7)
        WWDG1->SR = 0;
#else
        WWDG->SR = 0;
#endif
    }

    void WatchDogStm::Interrupt()
    {
        WatchDogRefresh();

        if (++missedFeedCount == maxMissedFeeds)
            onExpired();
    }

    void WatchDogStm::Feed()
    {
        missedFeedCount = 0;
    }
}
