#ifndef HAPTICWAND_H
#define HAPTICWAND_H

#include "hil.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define NUM_JOINTS  (6)			/* number of joints */
#define NUM_WORLD   (5)	        /* number of world coordinates */
#define NUM_DIGITAL_OUTPUT  (6) /* number of digital output channels */


/**
 *
 * HapticWand class is designed to control Quanser's 5DOF Haptic Wand. The joint coordinates
 * are read from encoder channels 0-5. Analog output channels 0-5 are used to drive the motors.
 *
 */
namespace Hardware
{
    class HAPTICWANDSHARED_EXPORT HapticWand : public HIL
    {
    public:
        HapticWand();

        /**
         * Opens the specified card of the given type. Configures digital I/O lines as outputs.
         *
         * @param cardType          A string identifying the type of card.
         * @param cardIdentifier    An integer identifying the particular
         *                          board among all the boards of the same type.
         */
        virtual void open(const char* cardType = "Q80", const int cardIdentifier = 0);

        /**
         * Enable a motor amplifiers.
         */
        void enableWand();

        /**
         * Disable a motor amplifiers.
         */
        void disableWand();

        /**
         * Calibrate the haptic wand.
         */
        void calibrateWand();

        /**
         * Resets the encoders to zero.
         */
        void resetEncoders();

        /**
         * Reads from encoder channels 0-5.
         * The size of the counts array must be at least 6.
         *
         * @param counts    The count values read from the encoder inputs.
         */
        void readEncoders( int* counts );

        /**
         * Writes user defined voltage values to analog output channels 0-5.
         * The size of the counts array must be at least 6.
         *
         * @param voltages  The voltage values to write to the analog outputs.
         */
        void writeAnalogs( const double* voltages );

        /**
         * Converts encoder counts from the Haptic 5-DOF Wand into joint angles in radians.
         * The parameter jointAngles are output as a 6-vector in order of the joints.
         */
        void jointAngles( double* jointAngles );

        // YAPILACAK milimetre milimetre, yoksa metre
        /**
         * Computes the end-effector position and orientation.
         * The parameter worldCoordinates are output. The first three elements of
         * the worldCoordinates denote the x, y and z position of the end-effector
         * in millimeters and the last two elements denote its orientation
         * (roll and pitch ) in radians.
         */
        void forwardKinematics( double* worldCoordinates );

    private:

        /**
         * Link lengths of the haptic wand links in meters
         */
        static const double l[7];

        /**
         * Analog output channels driving the haptic wand motors
         */
        static const unsigned int analogChannels[6];

        /**
         * Encoder input channels for the haptic wand joint encoders
         */
        static const unsigned int encoderChannels[6];

        /**
         * Digital output channels driving the amplifier enable lines
         */
        static const unsigned int digitalOutputChannels[6];
    };
}

#endif // HAPTICWAND_H
