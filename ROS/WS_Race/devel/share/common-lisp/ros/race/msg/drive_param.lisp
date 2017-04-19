; Auto-generated. Do not edit!


(cl:in-package race-msg)


;//! \htmlinclude drive_param.msg.html

(cl:defclass <drive_param> (roslisp-msg-protocol:ros-message)
  ((steer
    :reader steer
    :initarg :steer
    :type cl:float
    :initform 0.0)
   (throttle
    :reader throttle
    :initarg :throttle
    :type cl:float
    :initform 0.0))
)

(cl:defclass drive_param (<drive_param>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <drive_param>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'drive_param)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name race-msg:<drive_param> is deprecated: use race-msg:drive_param instead.")))

(cl:ensure-generic-function 'steer-val :lambda-list '(m))
(cl:defmethod steer-val ((m <drive_param>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader race-msg:steer-val is deprecated.  Use race-msg:steer instead.")
  (steer m))

(cl:ensure-generic-function 'throttle-val :lambda-list '(m))
(cl:defmethod throttle-val ((m <drive_param>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader race-msg:throttle-val is deprecated.  Use race-msg:throttle instead.")
  (throttle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <drive_param>) ostream)
  "Serializes a message object of type '<drive_param>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'throttle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <drive_param>) istream)
  "Deserializes a message object of type '<drive_param>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'throttle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<drive_param>)))
  "Returns string type for a message object of type '<drive_param>"
  "race/drive_param")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'drive_param)))
  "Returns string type for a message object of type 'drive_param"
  "race/drive_param")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<drive_param>)))
  "Returns md5sum for a message object of type '<drive_param>"
  "921b927d5a13c61c089a5528049b7b7a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'drive_param)))
  "Returns md5sum for a message object of type 'drive_param"
  "921b927d5a13c61c089a5528049b7b7a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<drive_param>)))
  "Returns full string definition for message of type '<drive_param>"
  (cl:format cl:nil "float32 steer~%float32 throttle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'drive_param)))
  "Returns full string definition for message of type 'drive_param"
  (cl:format cl:nil "float32 steer~%float32 throttle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <drive_param>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <drive_param>))
  "Converts a ROS message object to a list"
  (cl:list 'drive_param
    (cl:cons ':steer (steer msg))
    (cl:cons ':throttle (throttle msg))
))
