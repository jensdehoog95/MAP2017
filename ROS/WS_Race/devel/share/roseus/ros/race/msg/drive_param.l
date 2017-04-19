;; Auto-generated. Do not edit!


(when (boundp 'race::drive_param)
  (if (not (find-package "RACE"))
    (make-package "RACE"))
  (shadow 'drive_param (find-package "RACE")))
(unless (find-package "RACE::DRIVE_PARAM")
  (make-package "RACE::DRIVE_PARAM"))

(in-package "ROS")
;;//! \htmlinclude drive_param.msg.html


(defclass race::drive_param
  :super ros::object
  :slots (_steer _throttle ))

(defmethod race::drive_param
  (:init
   (&key
    ((:steer __steer) 0.0)
    ((:throttle __throttle) 0.0)
    )
   (send-super :init)
   (setq _steer (float __steer))
   (setq _throttle (float __throttle))
   self)
  (:steer
   (&optional __steer)
   (if __steer (setq _steer __steer)) _steer)
  (:throttle
   (&optional __throttle)
   (if __throttle (setq _throttle __throttle)) _throttle)
  (:serialization-length
   ()
   (+
    ;; float32 _steer
    4
    ;; float32 _throttle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _steer
       (sys::poke _steer (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _throttle
       (sys::poke _throttle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _steer
     (setq _steer (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _throttle
     (setq _throttle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get race::drive_param :md5sum-) "921b927d5a13c61c089a5528049b7b7a")
(setf (get race::drive_param :datatype-) "race/drive_param")
(setf (get race::drive_param :definition-)
      "float32 steer
float32 throttle

")



(provide :race/drive_param "921b927d5a13c61c089a5528049b7b7a")


