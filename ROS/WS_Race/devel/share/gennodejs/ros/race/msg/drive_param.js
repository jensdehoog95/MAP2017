// Auto-generated. Do not edit!

// (in-package race.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class drive_param {
  constructor() {
    this.steer = 0.0;
    this.throttle = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type drive_param
    // Serialize message field [steer]
    bufferInfo = _serializer.float32(obj.steer, bufferInfo);
    // Serialize message field [throttle]
    bufferInfo = _serializer.float32(obj.throttle, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type drive_param
    let tmp;
    let len;
    let data = new drive_param();
    // Deserialize message field [steer]
    tmp = _deserializer.float32(buffer);
    data.steer = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [throttle]
    tmp = _deserializer.float32(buffer);
    data.throttle = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'race/drive_param';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '921b927d5a13c61c089a5528049b7b7a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 steer
    float32 throttle
    
    `;
  }

};

module.exports = drive_param;
