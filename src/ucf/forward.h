#ifndef UCF_FORWARD_H
#define UCF_FORWARD_H

// UCF ported from https://github.com/AltimorTASDK/ucf

/// Raw stick units that normalise to 1.0.
#define UCF_STICK_MAX 80

/// Max raw off-axis value that still snaps to a cardinal.
#define UCF_CARDINAL_RANGE 6

/// Raw lstick travel over two frames that counts as a smash input (tauKhan).
#define UCF_SMASH_TRAVEL 75
#define UCF_SDI_TRAVEL 62
#define UCF_GUARD_PASS_TRAVEL 44

/// Top of the Guard pass zone on the rim: -0.6125 as Nana requantises it.
#define UCF_GUARD_PASS_MAX_Y (-78.0f / 128.0f)

/// Lowest lstick Y that suppresses the spot dodge.
#define UCF_ESCAPEN_PASS_MIN_Y -0.8000f

/// 0.6000 would desync Ice Climbers.
#define UCF_SQUATRV_THRESHOLD 0.5900f

#define UCF_PAD_BUFFER_SIZE 4
#define UCF_PAD_BUFFER_MASK (UCF_PAD_BUFFER_SIZE - 1)

#endif
