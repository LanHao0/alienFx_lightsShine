// dllmain.cpp : Defines the entry point for the DLL application.਍⌀椀渀挀氀甀搀攀 ∀猀琀搀愀昀砀⸀栀∀ഀഀ
਍䈀伀伀䰀 䄀倀䤀䔀一吀刀夀 䐀氀氀䴀愀椀渀⠀ 䠀䴀伀䐀唀䰀䔀 栀䴀漀搀甀氀攀Ⰰഀഀ
                       DWORD  ul_reason_for_call,਍                       䰀倀嘀伀䤀䐀 氀瀀刀攀猀攀爀瘀攀搀ഀഀ
                     )਍笀ഀഀ
    switch (ul_reason_for_call)਍    笀ഀഀ
    case DLL_PROCESS_ATTACH:਍    挀愀猀攀 䐀䰀䰀开吀䠀刀䔀䄀䐀开䄀吀吀䄀䌀䠀㨀ഀഀ
    case DLL_THREAD_DETACH:਍    挀愀猀攀 䐀䰀䰀开倀刀伀䌀䔀匀匀开䐀䔀吀䄀䌀䠀㨀ഀഀ
        break;਍    紀ഀഀ
    return TRUE;਍紀ഀഀ
਍�