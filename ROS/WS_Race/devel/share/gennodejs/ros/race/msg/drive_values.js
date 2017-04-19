// Auto-generated. Do not edit!

// (in-package race.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class drive_values {
  constructor() {
    this.pwm_drive = 0;
    this.pwm_angle = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type drive_values
    // Serialize message field [pwm_drive]
    bufferInfo = _serializer.int16(obj.pwm_drive, bufferInfo);
    // Serialize message field [pwm_angle]
    bufferInfo = _serializer.int16(obj.pwm_angle, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type drive_values
    let tmp;
    let len;
    let data = new drive_values();
    // Deserialize message field [pwm_drive]
    tmp = _deserializer.int16(buffer);
    data.pwm_drive = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [pwm_angle]
    tmp = _deserializer.int16(buffer);
    data.pwm_angle = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'race/drive_values';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '180768e2d6cce7b3f71749adb84f7b29';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 pwm_drive
    int16 pwm_angle
    
    `;
  }

};

module.exports = drive_values;
